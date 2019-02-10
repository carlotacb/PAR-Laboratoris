#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <malloc.h>
#include "const_seq.h"
#include "tareador.h"
#include <fftw3.h>

static fftwf_complex in_fftw[N][N][N];
static fftwf_complex tmp_fftw[N][N][N];
#if TEST
static fftwf_complex out_fftw[N][N][N];
#endif 

fftwf_plan p;
fftwf_plan p1d;

void start_plan_forward(fftwf_complex in_fftw[][N][N], fftwf_plan *p1d)
{
#if TEST
    p = fftwf_plan_dft_3d(N, N, N, (fftwf_complex *)in_fftw, (fftwf_complex *)in_fftw, FFTW_FORWARD, FFTW_ESTIMATE);
#endif 
    *p1d = fftwf_plan_dft_1d(N, (fftwf_complex *)in_fftw, (fftwf_complex *)in_fftw, FFTW_FORWARD, FFTW_ESTIMATE);
}

void init_complex_grid(fftwf_complex in_fftw[][N][N])
{
  int k,j,i;

  for (k = 0; k < N; k++) {
    tareador_start_task("v4_1");
    for (j = 0; j < N; j++)
      for (i = 0; i < N; i++)
      {
        in_fftw[k][j][i][0] = (float) (sin(M_PI*((float)i)/64.0)+sin(M_PI*((float)i)/32.0)+sin(M_PI*((float)i/16.0)));
        in_fftw[k][j][i][1] = 0;
#if TEST
        out_fftw[k][j][i][0]= in_fftw[k][j][i][0];
        out_fftw[k][j][i][1]= in_fftw[k][j][i][1];
#endif
      }
    tareador_end_task("v4_1");
  }
}

void transpose_xy_planes(fftwf_complex  tmp_fftw[][N][N], fftwf_complex in_fftw[][N][N])
{
    int k,j,i;

    for (k=0; k<N; k++) {
     tareador_start_task("v3_1");
     for (j=0; j<N; j++){
       for (i=0; i<N; i++)
       {
         tmp_fftw[k][i][j][0] = in_fftw[k][j][i][0];
         tmp_fftw[k][i][j][1] = in_fftw[k][j][i][1];
       }
     }
    tareador_end_task("v3_1");
    }
}

void transpose_zx_planes(fftwf_complex in_fftw[][N][N], fftwf_complex tmp_fftw[][N][N])
{
    int k, j, i;

    for (k=0; k<N; k++) {
     tareador_start_task("v3_2");
     for (j=0; j<N; j++){
       for (i=0; i<N; i++)
       {
         in_fftw[i][j][k][0] = tmp_fftw[k][j][i][0];
         in_fftw[i][j][k][1] = tmp_fftw[k][j][i][1];
       }
      }
     tareador_end_task("v3_2");
     }
}


void ffts1_planes(fftwf_plan p1d, fftwf_complex in_fftw[][N][N])
{
    int k,j;

    for (k=0; k<N; k++)  {
     tareador_start_task("v2_1");
     for (j=0; j<N; j++)
       fftwf_execute_dft( p1d, (fftwf_complex *)in_fftw[k][j][0], (fftwf_complex *)in_fftw[k][j][0]);
     tareador_end_task("v2_1");
    }
}


double getusec_() {
        struct timeval time;
        gettimeofday(&time, 0);
        return ((double)time.tv_sec * (double)1e6 + (double)time.tv_usec);
}


int main (int argc, char *argv[])
{
#if TEST
  int i,j,k;
#endif
  double stamp;

    /* Initialize Tareador analysis */
    tareador_ON ();

    printf("Start TEST :%d ======================================================================================\n",N);

    START_COUNT_TIME;

    tareador_start_task("start_plan_forward");
    start_plan_forward(in_fftw, &p1d);
    tareador_end_task("start_plan_forward");

    STOP_COUNT_TIME("3D FFT Plan Generation");

    printf("Start Init Grid and Execute FFT3D\n");

    START_COUNT_TIME;

    init_complex_grid(in_fftw);

    STOP_COUNT_TIME("Init Complex Grid FFT3D");

    START_COUNT_TIME;

    ffts1_planes(p1d, in_fftw);

    transpose_xy_planes(tmp_fftw, in_fftw);

    ffts1_planes(p1d, tmp_fftw);

    transpose_zx_planes(in_fftw, tmp_fftw);

    ffts1_planes(p1d, in_fftw);

    transpose_zx_planes(tmp_fftw, in_fftw);

    transpose_xy_planes(in_fftw, tmp_fftw);
     
    STOP_COUNT_TIME("Execution FFT3D");

    /* Finalize the Valgrind analysis */
    tareador_OFF ();

#if TEST 
    printf("Start Execute test FFT3D\n");
    START_COUNT_TIME;
    fftwf_execute_dft( p, (fftwf_complex *)out_fftw, (fftwf_complex *)out_fftw);
    STOP_COUNT_TIME("test FFT3D");
    printf("End Execute test FFT3D\n");
    fftwf_destroy_plan(p);

    int errors_count = 0;
    for (k = 0; k < N; k++)
      for (j = 0; j < N; j++)
         for (i = 0; i < N; i++)
         {
           if (!((fabs(in_fftw[k][j][i][0]-out_fftw[k][j][i][0]) < ERROR_ALLOWED) && (fabs(in_fftw[k][j][i][1]-out_fftw[k][j][i][1]) < ERROR_ALLOWED))) {
              printf ("\n\n\nError: %d %d %d,   %f %f %f %f errors so far %d\n",k,j,i, in_fftw[k][j][i][0],out_fftw[k][j][i][0],in_fftw[k][j][i][1],out_fftw[k][j][i][1],++errors_count);
              return 0; 
           }
         }
    printf("Test Succeded FFT3D\n");
#endif

    fftwf_destroy_plan(p1d);

    printf("End TEST :%d =========================================================================================\n",N);
    return 0;
}
