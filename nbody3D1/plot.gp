set terminal pngcairo enhanced font 'Verdana,12'

set title "comparaison des performances"

set xlabel "flags"
set ylabel "GFLOP/s"

set style data histogram
set style histogram cluster
set style fill solid border -1
set key left top

set output 'comparaison entre les compilateur pour code donné.png'
plot "perf_gcc.txt" using 2:xtic(1) title 'gcc', \
     "perf_clang.txt" using 2:xtic(1) title 'clang'

set output 'comparaison entre les compilateur pour version 1.png'
plot "perf_gcc.txt" using 3:xtic(1) title 'gcc', \
     "perf_clang.txt" using 3:xtic(1) title 'clang'

set output 'comparaison entre les compilateur pour version 2.png'
plot "perf_gcc.txt" using 4:xtic(1) title 'gcc', \
     "perf_clang.txt" using 4:xtic(1) title 'clang'

set output 'comparaison entre les compilateur pour version 3.png'
plot "perf_gcc.txt" using 5:xtic(1) title 'gcc', \
     "perf_clang.txt" using 5:xtic(1) title 'clang'