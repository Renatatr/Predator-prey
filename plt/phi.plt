set terminal pngcairo

set size ratio -1 # para deixar os eixos na mesma proporção
set yrange[1:500]
set xrange[1:500]
set cbrange [0:2]
set cbtics 1
#set xtics 50
#set ytics 50
unset xtics
unset ytics

set palette defined ( 0 "#ffffff",\
                      1 "#ff0000",\
                      2 "#0000ff")
I=0
while (I <= 500){
	set output sprintf("phi-%d.png", I)
	plot sprintf("../dat/phi-%d.dat", I) u ($1+1):($2+1):($3) matrix w image t""# plota o gráfico usando a ideia de matriz
	unset output
	I= I+10
}
