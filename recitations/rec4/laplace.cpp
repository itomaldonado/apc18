#define MAX(A,B) (((A) > (B)) ? (A) : (B))

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main() {

  double *T, *Tnew, *Tmp;
  double tol, var = DBL_MAX, top = 100.0;
  unsigned n, n2, maxIter, k, i, j, iter = 0;
  int itemsread;
  FILE *fout;
  n=1024;
  maxIter=1000;
  tol=0.05;
  // printf("Enter mesh size, max iterations and tolerance: ");
  //itemsread = scanf("%u ,%u ,%lf", &n, &maxIter, &tol);

  /*if (itemsread!=3) {
    fprintf(stderr, "Input error!\n");
    exit(-1);
    }*/

  #ifdef _OPENMP
    double startTime = omp_get_wtime();
  #else
    time_t startTime = clock();
  #endif

  n2 = n+2;
  T =(double *)calloc(n2*n2, sizeof(*T));
  Tnew =(double *) calloc(n2*n2, sizeof(*T));

  if (T == NULL || Tnew == NULL) {
    fprintf(stderr, "Not enough memory!\n");
    exit(EXIT_FAILURE);
  }

  // set boundary conditions
  #pragma omp parallel private(i,j,k,Tmp) shared(iter,tol,maxIter,n,n2,T,Tnew,var) //reduction(max:var)
  {
    
    #pragma omp single nowait
    {
      for (k=1; k<=n; k++) {
        T[(n+1)*n2+k] = k * top / (n+1);
        Tnew[(n+1)*n2+k] = k * top / (n+1);
        
        T[k*n2+n+1] = k * top / (n+1);
        Tnew[k*n2+n+1] = k * top / (n+1);
      }
    }

    while(var > tol && iter <= maxIter) {
      // single one increases iteration
      #pragma omp single
      {
        ++iter;
      }

      var = 0.0;
      for (i=1; i<=n; ++i) {
        for (j=1; j<=n; ++j) {
          Tnew[i*n2+j] = 0.25*( T[(i-1)*n2+j] + T[(i+1)*n2+j]
                                + T[i*n2+(j-1)] + T[i*n2+(j+1)] );
          var = MAX(var, fabs(Tnew[i*n2+j] - T[i*n2+j]));
        }
      }

      #pragma omp barrier

      #pragma single
      {
        Tmp=T; T=Tnew; Tnew=Tmp;
      }

      #pragma omp single nowait
      {
        if (iter%100 == 0)
          printf("iter: %8u, variation = %12.4lE\n", iter, var);
      }
    }
  }

  #ifdef _OPENMP
    double endTime = omp_get_wtime() - startTime;
  #else
    double endTime = (clock() - startTime) / (double) CLOCKS_PER_SEC;
  #endif

  

  printf("Elapsed time (s) = %.2lf\n", endTime);
  printf("Mesh size: %u\n", n);
  printf("Stopped at iteration: %u\n", iter);
  printf("Maximum error: %lE\n", var);

  // saving results to file
  /*fout = fopen("results", "w");
  if (fout == NULL) {
    perror("results");
    exit(-1);
  }
  for (i=1; i<=n; ++i)
    for (j=1; j<=n; +t+j)
      fprintf(fout, "%8u %8u %18.9lE\n", i, j, T[i*n2+j]);
      fclose(fout);*/
  free(T);
  free(Tnew);
  return 0;
}
