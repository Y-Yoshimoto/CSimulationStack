reset
set xr[24:96]
set yr[24:96]
set cbrange[-1.2:1.2]
set term gif truecolor size 800, 800
set term gif enhanced animate delay 20
set palette defined (-1 "#007EB1",  0 "#F5F5F5", 1 "#D93448")
set pm3d map corners2color c1
set palette defined (0 "#0571b0",1 "#92c5de",2 "#f7f7f7",3 "#f4a582",4 "#ca0020")
set pm3d map corners2color c1
unset key
set output "Spin_Map.gif"
set title "ti=0
splot "Spin_map0.dat" using 1:2:6 with pm3d,"Spin_map0.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=1
splot "Spin_map1.dat" using 1:2:6 with pm3d,"Spin_map1.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=2
splot "Spin_map2.dat" using 1:2:6 with pm3d,"Spin_map2.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=3
splot "Spin_map3.dat" using 1:2:6 with pm3d,"Spin_map3.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=4
splot "Spin_map4.dat" using 1:2:6 with pm3d,"Spin_map4.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=5
splot "Spin_map5.dat" using 1:2:6 with pm3d,"Spin_map5.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=6
splot "Spin_map6.dat" using 1:2:6 with pm3d,"Spin_map6.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=7
splot "Spin_map7.dat" using 1:2:6 with pm3d,"Spin_map7.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=8
splot "Spin_map8.dat" using 1:2:6 with pm3d,"Spin_map8.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=9
splot "Spin_map9.dat" using 1:2:6 with pm3d,"Spin_map9.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=10
splot "Spin_map10.dat" using 1:2:6 with pm3d,"Spin_map10.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=11
splot "Spin_map11.dat" using 1:2:6 with pm3d,"Spin_map11.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=12
splot "Spin_map12.dat" using 1:2:6 with pm3d,"Spin_map12.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=13
splot "Spin_map13.dat" using 1:2:6 with pm3d,"Spin_map13.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=14
splot "Spin_map14.dat" using 1:2:6 with pm3d,"Spin_map14.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=15
splot "Spin_map15.dat" using 1:2:6 with pm3d,"Spin_map15.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=16
splot "Spin_map16.dat" using 1:2:6 with pm3d,"Spin_map16.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=17
splot "Spin_map17.dat" using 1:2:6 with pm3d,"Spin_map17.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=18
splot "Spin_map18.dat" using 1:2:6 with pm3d,"Spin_map18.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=19
splot "Spin_map19.dat" using 1:2:6 with pm3d,"Spin_map19.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=20
splot "Spin_map20.dat" using 1:2:6 with pm3d,"Spin_map20.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=21
splot "Spin_map21.dat" using 1:2:6 with pm3d,"Spin_map21.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=22
splot "Spin_map22.dat" using 1:2:6 with pm3d,"Spin_map22.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=23
splot "Spin_map23.dat" using 1:2:6 with pm3d,"Spin_map23.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=24
splot "Spin_map24.dat" using 1:2:6 with pm3d,"Spin_map24.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=25
splot "Spin_map25.dat" using 1:2:6 with pm3d,"Spin_map25.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=26
splot "Spin_map26.dat" using 1:2:6 with pm3d,"Spin_map26.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=27
splot "Spin_map27.dat" using 1:2:6 with pm3d,"Spin_map27.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=28
splot "Spin_map28.dat" using 1:2:6 with pm3d,"Spin_map28.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=29
splot "Spin_map29.dat" using 1:2:6 with pm3d,"Spin_map29.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=30
splot "Spin_map30.dat" using 1:2:6 with pm3d,"Spin_map30.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=31
splot "Spin_map31.dat" using 1:2:6 with pm3d,"Spin_map31.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=32
splot "Spin_map32.dat" using 1:2:6 with pm3d,"Spin_map32.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=33
splot "Spin_map33.dat" using 1:2:6 with pm3d,"Spin_map33.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=34
splot "Spin_map34.dat" using 1:2:6 with pm3d,"Spin_map34.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=35
splot "Spin_map35.dat" using 1:2:6 with pm3d,"Spin_map35.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=36
splot "Spin_map36.dat" using 1:2:6 with pm3d,"Spin_map36.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=37
splot "Spin_map37.dat" using 1:2:6 with pm3d,"Spin_map37.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=38
splot "Spin_map38.dat" using 1:2:6 with pm3d,"Spin_map38.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=39
splot "Spin_map39.dat" using 1:2:6 with pm3d,"Spin_map39.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=40
splot "Spin_map40.dat" using 1:2:6 with pm3d,"Spin_map40.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=41
splot "Spin_map41.dat" using 1:2:6 with pm3d,"Spin_map41.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=42
splot "Spin_map42.dat" using 1:2:6 with pm3d,"Spin_map42.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=43
splot "Spin_map43.dat" using 1:2:6 with pm3d,"Spin_map43.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=44
splot "Spin_map44.dat" using 1:2:6 with pm3d,"Spin_map44.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=45
splot "Spin_map45.dat" using 1:2:6 with pm3d,"Spin_map45.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=46
splot "Spin_map46.dat" using 1:2:6 with pm3d,"Spin_map46.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=47
splot "Spin_map47.dat" using 1:2:6 with pm3d,"Spin_map47.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=48
splot "Spin_map48.dat" using 1:2:6 with pm3d,"Spin_map48.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=49
splot "Spin_map49.dat" using 1:2:6 with pm3d,"Spin_map49.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=50
splot "Spin_map50.dat" using 1:2:6 with pm3d,"Spin_map50.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=51
splot "Spin_map51.dat" using 1:2:6 with pm3d,"Spin_map51.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=52
splot "Spin_map52.dat" using 1:2:6 with pm3d,"Spin_map52.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=53
splot "Spin_map53.dat" using 1:2:6 with pm3d,"Spin_map53.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=54
splot "Spin_map54.dat" using 1:2:6 with pm3d,"Spin_map54.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=55
splot "Spin_map55.dat" using 1:2:6 with pm3d,"Spin_map55.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=56
splot "Spin_map56.dat" using 1:2:6 with pm3d,"Spin_map56.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=57
splot "Spin_map57.dat" using 1:2:6 with pm3d,"Spin_map57.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=58
splot "Spin_map58.dat" using 1:2:6 with pm3d,"Spin_map58.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=59
splot "Spin_map59.dat" using 1:2:6 with pm3d,"Spin_map59.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=60
splot "Spin_map60.dat" using 1:2:6 with pm3d,"Spin_map60.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=61
splot "Spin_map61.dat" using 1:2:6 with pm3d,"Spin_map61.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=62
splot "Spin_map62.dat" using 1:2:6 with pm3d,"Spin_map62.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=63
splot "Spin_map63.dat" using 1:2:6 with pm3d,"Spin_map63.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=64
splot "Spin_map64.dat" using 1:2:6 with pm3d,"Spin_map64.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=65
splot "Spin_map65.dat" using 1:2:6 with pm3d,"Spin_map65.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=66
splot "Spin_map66.dat" using 1:2:6 with pm3d,"Spin_map66.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=67
splot "Spin_map67.dat" using 1:2:6 with pm3d,"Spin_map67.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=68
splot "Spin_map68.dat" using 1:2:6 with pm3d,"Spin_map68.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=69
splot "Spin_map69.dat" using 1:2:6 with pm3d,"Spin_map69.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=70
splot "Spin_map70.dat" using 1:2:6 with pm3d,"Spin_map70.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=71
splot "Spin_map71.dat" using 1:2:6 with pm3d,"Spin_map71.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=72
splot "Spin_map72.dat" using 1:2:6 with pm3d,"Spin_map72.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=73
splot "Spin_map73.dat" using 1:2:6 with pm3d,"Spin_map73.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=74
splot "Spin_map74.dat" using 1:2:6 with pm3d,"Spin_map74.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=75
splot "Spin_map75.dat" using 1:2:6 with pm3d,"Spin_map75.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=76
splot "Spin_map76.dat" using 1:2:6 with pm3d,"Spin_map76.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=77
splot "Spin_map77.dat" using 1:2:6 with pm3d,"Spin_map77.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=78
splot "Spin_map78.dat" using 1:2:6 with pm3d,"Spin_map78.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=79
splot "Spin_map79.dat" using 1:2:6 with pm3d,"Spin_map79.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=80
splot "Spin_map80.dat" using 1:2:6 with pm3d,"Spin_map80.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=81
splot "Spin_map81.dat" using 1:2:6 with pm3d,"Spin_map81.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=82
splot "Spin_map82.dat" using 1:2:6 with pm3d,"Spin_map82.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=83
splot "Spin_map83.dat" using 1:2:6 with pm3d,"Spin_map83.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=84
splot "Spin_map84.dat" using 1:2:6 with pm3d,"Spin_map84.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=85
splot "Spin_map85.dat" using 1:2:6 with pm3d,"Spin_map85.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=86
splot "Spin_map86.dat" using 1:2:6 with pm3d,"Spin_map86.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=87
splot "Spin_map87.dat" using 1:2:6 with pm3d,"Spin_map87.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=88
splot "Spin_map88.dat" using 1:2:6 with pm3d,"Spin_map88.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=89
splot "Spin_map89.dat" using 1:2:6 with pm3d,"Spin_map89.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=90
splot "Spin_map90.dat" using 1:2:6 with pm3d,"Spin_map90.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=91
splot "Spin_map91.dat" using 1:2:6 with pm3d,"Spin_map91.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=92
splot "Spin_map92.dat" using 1:2:6 with pm3d,"Spin_map92.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=93
splot "Spin_map93.dat" using 1:2:6 with pm3d,"Spin_map93.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=94
splot "Spin_map94.dat" using 1:2:6 with pm3d,"Spin_map94.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=95
splot "Spin_map95.dat" using 1:2:6 with pm3d,"Spin_map95.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=96
splot "Spin_map96.dat" using 1:2:6 with pm3d,"Spin_map96.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=97
splot "Spin_map97.dat" using 1:2:6 with pm3d,"Spin_map97.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=98
splot "Spin_map98.dat" using 1:2:6 with pm3d,"Spin_map98.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=99
splot "Spin_map99.dat" using 1:2:6 with pm3d,"Spin_map99.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=100
splot "Spin_map100.dat" using 1:2:6 with pm3d,"Spin_map100.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set title "ti=101
splot "Spin_map101.dat" using 1:2:6 with pm3d,"Spin_map101.dat" using 1:2:3:4:5:6 every 1:1 with vector lc rgb "black"
set output