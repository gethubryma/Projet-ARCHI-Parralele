#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef float              f32;
typedef double             f64;
typedef unsigned long long u64;

typedef struct particle_s {
  f32 *x, *y, *z;
  f32 *vx, *vy, *vz;
} particle_t;

void init(particle_t *p, u64 n)
{
  #pragma omp parallel for
  for (u64 i = 0; i < n; i++)
  {
    u64 r1 = (u64)rand();
    u64 r2 = (u64)rand();
    f32 sign = (r1 > r2) ? 1 : -1;

    p->x[i] = sign * (f32)rand() / (f32)RAND_MAX;
    p->y[i] = (f32)rand() / (f32)RAND_MAX;
    p->z[i] = sign * (f32)rand() / (f32)RAND_MAX;

    p->vx[i] = (f32)rand() / (f32)RAND_MAX;
    p->vy[i] = sign * (f32)rand() / (f32)RAND_MAX;
    p->vz[i] = (f32)rand() / (f32)RAND_MAX;
  }
}

void move_particles(particle_t *p, const f32 dt, u64 n)
{
  const f32 softening = 1e-20;

  #pragma omp parallel for
  for (u64 i = 0; i < n; i++)
  {
    f32 fx = 0.0;
    f32 fy = 0.0;
    f32 fz = 0.0;
    //parallesiser les boucles internes 
    #pragma omp parallel for reduction(+:fx,fy,fz)
    for (u64 j = 0; j < n; j++)
    {
      const f32 dx = p->x[j] - p->x[i];
      const f32 dy = p->y[j] - p->y[i];
      const f32 dz = p->z[j] - p->z[i];

      const f32 d_2 = (dx * dx) + (dy * dy) + (dz * dz) + softening;
      
      //remplacer la fonction pow avec la racine carrée
	    const f32 d_3_over_2 = d_2 * sqrt(d_2);

      //calculer l'inverse de d_3_over_2 ensuite utiliser la multiplication (*)
      const f32 inv_d_3_over_2 = 1.0 / d_3_over_2;
      fx += dx * inv_d_3_over_2; 
      fy += dy * inv_d_3_over_2;
      fz += dz * inv_d_3_over_2; 
    }

    p->vx[i] += dt * fx;
    p->vy[i] += dt * fy;
    p->vz[i] += dt * fz;
  }

  #pragma omp parallel for
  for (u64 i = 0; i < n; i++)
  {
    p->x[i] += dt * p->vx[i];
    p->y[i] += dt * p->vy[i];
    p->z[i] += dt * p->vz[i];
  }
}

int main(int argc, char **argv)
{
  const u64 n = (argc > 1) ? atoll(argv[1]) : 16384;
  const u64 steps = 13;
  const f32 dt = 0.01;

  f64 rate = 0.0, drate = 0.0;
  const u64 warmup = 3;

  particle_t p;
  p.x = malloc(sizeof(f32) * n);
  p.y = malloc(sizeof(f32) * n);
  p.z = malloc(sizeof(f32) * n);
  p.vx = malloc(sizeof(f32) * n);
  p.vy = malloc(sizeof(f32) * n);
  p.vz = malloc(sizeof(f32) * n);

  const u64 s = sizeof(f32) * 6 * n;

  printf("\n\033[1mTotal memory size:\033[0m %llu B, %llu KiB, %llu MiB\n\n", s, s >> 10, s >> 20);

  printf("\033[1m%5s %10s %10s %8s\033[0m\n", "Step", "Time, s", "Interact/s", "GFLOP/s");
  fflush(stdout);

  for (u64 i = 0; i < steps; i++)
  {
    const f64 start = omp_get_wtime();

    move_particles(&p, dt, n);

    const f64 end = omp_get_wtime();

    const f32 h1 = (f32)(n) * (f32)(n);
    const f32 h2 = (17.0 * h1 + 6.0 * (f32)n + 6.0 * (f32)n) * 1e-9;

    if (i >= warmup)
    {
      rate += h2 / (f32)(end - start);
      drate += (h2 * h2) / (f32)((end - start) * (end - start));
    }

    printf("%5llu %10.3e %10.3e %8.1f %s\n", i, (end - start), h1 / (end - start), h2 / (end - start),
           (i < warmup) ? "(warm up)" : "");

    fflush(stdout);
  }

  rate /= (f64)(steps - warmup);
  drate = sqrt(drate / (f64)(steps - warmup) - (rate * rate));

  printf("-----------------------------------------------------\n");
  printf("\033[1m%s %4s \033[42m%10.1lf +- %.1lf GFLOP/s\033[0m\n", "Average performance:", "", rate, drate);
  printf("-----------------------------------------------------\n");

  free(p.x);
  free(p.y);
  free(p.z);
  free(p.vx);
  free(p.vy);
  free(p.vz);

  return 0;
}
