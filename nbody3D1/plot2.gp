set terminal pngcairo enhanced font 'Verdana,12'

set title "Histogramme comparant les perf de chaque version"

set xlabel "flags"
set ylabel "perf"

set key left top

set style data histograms
set style histogram cluster gap 1

set xtics rotate by -45
set style fill solid border -1


set output 'compar entre flags avec gcc.png'
plot 'perf_gcc.txt' using 2:xtic(1) t "source", \
     'perf_gcc.txt' using 3:xtic(1) t "version 1", \
     'perf_gcc.txt' using 4:xtic(1) t "version 2", \
     'perf_gcc.txt' using 5:xtic(1) t "version 3"      

set output 'compar entre flags avec clang.png'
plot 'perf_clang.txt' using 2:xtic(1) t "source", \
     'perf_clang.txt' using 3:xtic(1) t "version 1", \
     'perf_clang.txt' using 4:xtic(1) t "version 2", \
     'perf_clang.txt' using 5:xtic(1) t "version 3"      
