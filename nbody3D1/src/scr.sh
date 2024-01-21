#!/bin/bash

make clean
make CC=gcc OFL=-O0 

./nbody3D > ../data/source/gcc_o0.txt
./nbody_vers1 > ../data/vers1/gcc_o0.txt
./nbody_vers2 > ../data/vers2/gcc_o0.txt
./nbody_vers3 > ../data/vers3/gcc_o0.txt

make clean
make CC=gcc OFL=-O2 

./nbody3D > ../data/source/gcc_o2.txt
./nbody_vers1 > ../data/vers1/gcc_o2.txt
./nbody_vers2 > ../data/vers2/gcc_o2.txt
./nbody_vers3 > ../data/vers3/gcc_o2.txt

make clean
make CC=gcc OFL=-O3 

./nbody3D > ../data/source/gcc_o3.txt
./nbody_vers1 > ../data/vers1/gcc_o3.txt
./nbody_vers2 > ../data/vers2/gcc_o3.txt
./nbody_vers3 > ../data/vers3/gcc_o3.txt

make clean
make CC=gcc OFL=-Ofast 

./nbody3D > ../data/source/gcc_ofast.txt
./nbody_vers1 > ../data/vers1/gcc_ofast.txt
./nbody_vers2 > ../data/vers2/gcc_ofast.txt
./nbody_vers3 > ../data/vers3/gcc_ofast.txt

make clean
make CC=clang OFL=-O0 

./nbody3D > ../data/source/CLANG_o0.txt
./nbody_vers1 > ../data/vers1/CLANG_o0.txt
./nbody_vers2 > ../data/vers2/CLANG_o0.txt
./nbody_vers3 > ../data/vers3/CLANG_o0.txt

make clean
make CC=clang OFL=-O2 

./nbody3D > ../data/source/CLANG_o2.txt
./nbody_vers1 > ../data/vers1/CLANG_o2.txt
./nbody_vers2 > ../data/vers2/CLANG_o2.txtt
./nbody_vers3 > ../data/vers3/CLANG_o2.txt

make clean
make CC=clang OFL=-O3 

./nbody3D > ../data/source/CLANG_o3.txt
./nbody_vers1 > ../data/vers1/CLANG_o3.txt
./nbody_vers2 > ../data/vers2/CLANG_o3.txt
./nbody_vers3 > ../data/vers3/CLANG_o3.txt

make clean
make CC=clang OFL=-Ofast 

./nbody3D > ../data/source/CLANG_ofast.txt
./nbody_vers1 > ../data/vers1/CLANG_ofast.txt
./nbody_vers2 > ../data/vers2/CLANG_ofast.txt
./nbody_vers3 > ../data/vers3/CLANG_ofast.txt
