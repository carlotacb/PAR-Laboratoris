# C compiler
OMPC    = gcc
OPT2 	= -O2
OPTG0 	= -g -O0
CFLAGS  = -std=c99 -Wall
OPENMP	= -fopenmp
LFLAGS  = -lm
CINCL    = -I.
CLIBS    = -L.

# Tareador compiler
TAREADORCC = tar-clang
TAREADOR_FLAGS = -tareador-lite 
#TAREADOR_FLAGS = -tareador-lite -isystem/scratch/nas/1/par0/Soft


TARGETS	= multisort multisort-tareador multisort-omp
all: $(TARGETS)

kernels.o: kernels.c 
	$(OMPC) -c $(CFLAGS) $(OPT2) $^ -o $@ 

multisort: multisort.c kernels.o
	$(OMPC) $(CFLAGS) $(OPT2) $+ $(LFLAGS) -o $@ 

multisort-tareador: multisort-tareador.c kernels-tareador.c
	$(TAREADORCC) $(TAREADOR_FLAGS) $(CFLAGS) $(OPTG0) $+ $(CINCL) $(LFLAGS) -o $@ $(CLIBS)

multisort-omp: multisort-omp.c  kernels.o
	$(OMPC) $(CFLAGS) $(OPT2) $(OPENMP) $+ $(LFLAGS) -o $@ 

clean:
	rm -fr $(TARGETS) *.o .tareador_precomputed* *.log

ultraclean:
	rm -fr $(TARGETS) *.o .tareador_precomputed* *.prv *.pcf *.row dependency_graph* *.times.txt lab4-omp* *.ps *.txt *.log TRACE.* set-0 logs

