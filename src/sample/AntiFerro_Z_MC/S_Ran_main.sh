#!/bin/sh
date "+%m,%d_%H,%M,%S"
NOW_TIME=`date "+%m,%d_%H,%M,%S"`
gcc main.c -lMT -lm -fopenmp -Ofast -o $NOW_TIME.out
time ./$NOW_TIME.out
rm $NOW_TIME.out
gnuplot <<EOF
#load "Mag+Energy_PT.plot"
#load "Mag+Energy.plot"
load "Spingif.plt"
EOF

rm Spin_map*.dat

fullpath=`pwd`
string_path=${fullpath##*/}
#scp G_Energy.png canis:Dropbox/$string_path.png
#scp Spin_Map.gif canis:Dropbox/