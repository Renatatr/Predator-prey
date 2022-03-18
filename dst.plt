set terminal tikz size 8.4cm, 4.0cm fontscale 0.8 fulldoc dl 0.5
set output "dst.tex"

set xlabel offset  0.0, 0.2 "$t$"
set ylabel offset  0.5, 0.0 "$\\rho_i$"
#set xrange [1e4:1.5e4]
set yrange [0:1]
#set xtics  offset 0.0, 0.0 
#set ytics  offset 1.0, 0.0
set xtics 1000
set key at graph 0.9, 0.95 horizontal Left reverse samplen 0.5 width 0.5

plot \
"dst.dat" u ($0):($1) w l lc rgb "#ff0000"  t"$1$" ,\
"dst.dat" u ($0):($2) w l lc rgb "#0000ff"  t"$2$" ,\
"dst.dat" u ($0):($3) w l lc rgb "#ffff00"  t"$3$"  


unset output
