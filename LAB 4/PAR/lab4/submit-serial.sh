#!/bin/csh
# following option makes sure the job will run in the current directory
#$ -cwd
# following option makes sure the job has the same environmnent variables as the submission shell
#$ -V
# Canviar el nom del job
#$ -N lab2-omp

setenv PROG multisort
make $PROG

setenv size 32768
setenv sort_size 32
setenv merge_size 512
./$PROG $size $sort_size $merge_size > ${PROG}.times.txt
