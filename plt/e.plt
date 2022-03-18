set terminal pngcairo

set size ratio -1 # para deixar os eixos na mesma proporção
set yrange[0:500]
set xrange[0:500]
#set cbrange [0:2]
#set cbtics 1
set xtics 50
set ytics 50
set palette rgbformulae -21, -22, -23

I=0
while (I <= 500){
	set output sprintf("emp-%d.png", I)
	plot sprintf("../dat/emp-%d.dat", I) u ($1+1):($2+1):($3) matrix w image t""# plota o gráfico usando a ideia de matriz
	unset output
	I= I+10
}
