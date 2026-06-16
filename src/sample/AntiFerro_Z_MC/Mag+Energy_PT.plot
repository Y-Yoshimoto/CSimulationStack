reset

set xlabel "Hz"
#set xlabel "T"
set term png truecolor size 1024,768


set title "Magnetization"
set output "G_Magnetization.png"
set ylabel "m"
plot \
'result0.10.dat' using 1:2:3 with yerrorlines,\
'result0.20.dat' using 1:2:3 with yerrorlines,\
'result0.30.dat' using 1:2:3 with yerrorlines,\
'result0.40.dat' using 1:2:3 with yerrorlines,\
'result0.50.dat' using 1:2:3 with yerrorlines,\
'result0.60.dat' using 1:2:3 with yerrorlines,\
'result0.70.dat' using 1:2:3 with yerrorlines,\
'result0.80.dat' using 1:2:3 with yerrorlines,\
'result0.90.dat' using 1:2:3 with yerrorlines,\
'result1.00.dat' using 1:2:3 with yerrorlines

set output

set title "Magnetic_Susceptibility"
set output "G_Magnetic_Susceptibility.png"
set ylabel "X"
plot \
'result0.10.dat' using 1:4:5 with yerrorlines,\
'result0.20.dat' using 1:4:5 with yerrorlines,\
'result0.30.dat' using 1:4:5 with yerrorlines,\
'result0.40.dat' using 1:4:5 with yerrorlines,\
'result0.50.dat' using 1:4:5 with yerrorlines,\
'result0.60.dat' using 1:4:5 with yerrorlines,\
'result0.70.dat' using 1:4:5 with yerrorlines,\
'result0.80.dat' using 1:4:5 with yerrorlines,\
'result0.90.dat' using 1:4:5 with yerrorlines,\
'result1.00.dat' using 1:4:5 with yerrorlines
set output

set title "Binder_Parameter"
set output "G_Binder_Parameter.png"
set ylabel "g"
plot \
'result0.10.dat' using 1:6:7 with yerrorlines,\
'result0.20.dat' using 1:6:7 with yerrorlines,\
'result0.30.dat' using 1:6:7 with yerrorlines,\
'result0.40.dat' using 1:6:7 with yerrorlines,\
'result0.50.dat' using 1:6:7 with yerrorlines,\
'result0.60.dat' using 1:6:7 with yerrorlines,\
'result0.70.dat' using 1:6:7 with yerrorlines,\
'result0.80.dat' using 1:6:7 with yerrorlines,\
'result0.90.dat' using 1:6:7 with yerrorlines,\
'result1.00.dat' using 1:6:7 with yerrorlines
set output


set title "Energy"
set output "G_Energy.png"
set ylabel "E"
plot \
'result0.10.dat' using 1:8:9 with yerrorlines,\
'result0.20.dat' using 1:8:9 with yerrorlines,\
'result0.30.dat' using 1:8:9 with yerrorlines,\
'result0.40.dat' using 1:8:9 with yerrorlines,\
'result0.50.dat' using 1:8:9 with yerrorlines,\
'result0.60.dat' using 1:8:9 with yerrorlines,\
'result0.70.dat' using 1:8:9 with yerrorlines,\
'result0.80.dat' using 1:8:9 with yerrorlines,\
'result0.90.dat' using 1:8:9 with yerrorlines,\
'result1.00.dat' using 1:8:9 with yerrorlines
set output

set output

set title "Heat_capacity"
set output "G_Heat_capacity.png"
set ylabel "C"
plot \
'result0.10.dat' using 1:10:11 with yerrorlines,\
'result0.20.dat' using 1:10:11 with yerrorlines,\
'result0.30.dat' using 1:10:11 with yerrorlines,\
'result0.40.dat' using 1:10:11 with yerrorlines,\
'result0.50.dat' using 1:10:11 with yerrorlines,\
'result0.60.dat' using 1:10:11 with yerrorlines,\
'result0.70.dat' using 1:10:11 with yerrorlines,\
'result0.80.dat' using 1:10:11 with yerrorlines,\
'result0.90.dat' using 1:10:11 with yerrorlines,\
'result1.00.dat' using 1:10:11 with yerrorlines
set output

reset
set title "sMagnetization"
set output "G_sMagnetization.png"
set ylabel "sm"
plot \
'result0.10.dat' using 1:12:13 with yerrorlines,\
'result0.20.dat' using 1:12:13 with yerrorlines,\
'result0.30.dat' using 1:12:13 with yerrorlines,\
'result0.40.dat' using 1:12:13 with yerrorlines,\
'result0.50.dat' using 1:12:13 with yerrorlines,\
'result0.60.dat' using 1:12:13 with yerrorlines,\
'result0.70.dat' using 1:12:13 with yerrorlines,\
'result0.80.dat' using 1:12:13 with yerrorlines,\
'result0.90.dat' using 1:12:13 with yerrorlines,\
'result1.00.dat' using 1:12:13 with yerrorlines
set output

reset
set title "sMagnetic_Susceptibility"
set output "G_sMagnetic_Susceptibility.png"
set ylabel "sX"
plot \
'result0.10.dat' using 1:14:15 with yerrorlines,\
'result0.20.dat' using 1:14:15 with yerrorlines,\
'result0.30.dat' using 1:14:15 with yerrorlines,\
'result0.40.dat' using 1:14:15 with yerrorlines,\
'result0.50.dat' using 1:14:15 with yerrorlines,\
'result0.60.dat' using 1:14:15 with yerrorlines,\
'result0.70.dat' using 1:14:15 with yerrorlines,\
'result0.80.dat' using 1:14:15 with yerrorlines,\
'result0.90.dat' using 1:14:15 with yerrorlines,\
'result1.00.dat' using 1:14:15 with yerrorlines
set output

reset
set title "sBinder_Parameter"
set output "G_sBinder_Parameter.png"
set ylabel "sg"
plot \
'result0.10.dat' using 1:16:17 with yerrorlines,\
'result0.20.dat' using 1:16:17 with yerrorlines,\
'result0.30.dat' using 1:16:17 with yerrorlines,\
'result0.40.dat' using 1:16:17 with yerrorlines,\
'result0.50.dat' using 1:16:17 with yerrorlines,\
'result0.60.dat' using 1:16:17 with yerrorlines,\
'result0.70.dat' using 1:16:17 with yerrorlines,\
'result0.80.dat' using 1:16:17 with yerrorlines,\
'result0.90.dat' using 1:16:17 with yerrorlines,\
'result1.00.dat' using 1:16:17 with yerrorlines
set output
