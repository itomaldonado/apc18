#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "time.h"
#include <sys/time.h>
#include <float.h>  // For: DBL_EPSILON

#ifdef _OPENMP 
#include<omp.h> 
#endif

#define EPS 0.00001

struct timeval start, end;
double duration;


int main(int argc, char **argv)
{
  int n=1024;
  int i, j, k;

  double **a = new double*[n];
  for(int i = 0; i < n; ++i) {
    a[i] = new double[n];
  }
  double **b = new double*[n];
  for(int i = 0; i < n; ++i) {
    b[i] = new double[n];
  }
  double **c = new double*[n];
  for(int i = 0; i < n; ++i) {
    c[i] = new double[n];
  }
  double **check = new double*[n];
  for(int i = 0; i < n; ++i) {
    check[i] = new double[n];
  }

  if ( a == NULL || b == NULL || c == NULL) {
    fprintf(stderr, "Not enough memory!\n");
    exit(EXIT_FAILURE);
  }

  for (i=0; i<n; i++)
    for (j=0; j<n; j++) {
      a[i][j] = ((double)rand())/((double)RAND_MAX);
      b[i][j] = ((double)rand())/((double)RAND_MAX);
      c[i][j] = 0.0;
    }

  for (i=0; i<n; i++)
    for (k=0; k<n; k++)
      for (j=0; j<n; j++)
        check[i][j] += a[i][k]*b[k][j];

  gettimeofday(&start, NULL);
#pragma omp parallel for private(i,k,j) shared(a,b,c,n)
  for (i=0; i<n; i++)
    for (k=0; k<n; k++)
      for (j=0; j<n; j++)
        c[i][j] += a[i][k]*b[k][j];

  gettimeofday(&end, NULL);

  // Check for correctedness
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      if(abs(check[i][j] - c[i][j]) > n*DBL_EPSILON ) {
        printf("Calculated matrix is incorrect...");
        return -1;
      }

  duration = (double)((end.tv_usec - start.tv_usec)/1.0e6 + end.tv_sec - start.tv_sec);
  printf ("Take %.6f second to compute \n", duration);


//check a random element
  i = rand()%n;
  j = rand()%n;
  double d = 0.0;
  for (k=0; k<n; k++)
    d += a[i][k]*b[k][j];

  //  printf("Check on a random element: %18.9lE\n", fabs(d-c[i][j]));
  // free the array
 for(int i = 0; i < n; ++i) {
    delete [] a[i];
  }
  delete [] a;
  for(int i = 0; i < n; ++i) {
    delete [] b[i];
  }
  delete [] b;
  for(int i = 0; i < n; ++i) {
    delete [] c[i];
  }
  delete [] c;

  return 0;

}
