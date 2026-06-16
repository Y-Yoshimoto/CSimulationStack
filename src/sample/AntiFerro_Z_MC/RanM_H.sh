#!/bin/sh
date "+%m,%d_%H,%M,%S"
NOW_TIME=`date "+%m,%d_%H,%M,%S"`
mpicc main_MPI.c -lMT -lm -Ofast -fopenmp -o $NOW_TIME.out
time mpirun -np 160 ./$NOW_TIME.out
rm $NOW_TIME.out
gnuplot <<EOF
load "Mag+Energy.plot"
EOF

fullpath=`pwd`
string_path=${fullpath##*/}
#scp G_Energy.png canis:Dropbox/$string_path.png