CC=gcc clang 

CFLAGS=-march=native -g3

OFLAGS=-fopenmp 
OFL=-O2 -O3 -Ofast

MY_O = -funroll-loops -finline-functions -ftree-vectorize -fno-omit-frame-pointer  $< -o $@ -lm -fopenmp

all: nbody3D nbody_vers1 nbody_vers2 nbody_vers3 nbody_vers4

nbody3D: nbody.c
	$(CC) $(CFLAGS) $(OFL) $(OFLAGS) $< -o $@ -lm

nbody_vers1: nbody_vers1.c
	$(CC) -g -march=native -mavx2 $(OFL) $(MY_O)

nbody_vers2: nbody_vers2.c
	$(CC) -g -march=native -mavx2 $(OFL) $(MY_O)

nbody_vers3: nbody_vers3.c
	$(CC) -g -march=native -mavx2 $(OFL) $(MY_O)

nbody_vers4: position.c
	$(CC) -g -march=native -mavx2 $(OFL) $(MY_O)

clean:
	rm -Rf *~ nbody3D nbody_vers1 nbody_vers2 nbody_vers3 nbody_vers4 *.optrpt

