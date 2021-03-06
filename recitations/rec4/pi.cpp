/* Exercise: Pi
 *
 * In this exercise you will determine the value
 * of PI using the integral  of
 *    4/(1+x*x) between 0 and 1.
 *
 * The integral is approximated by a sum of n intervals.
 *
 * The approximation to the integral in each interval is:
 *    (1/n)*4/(1+x*x).
 */
#include <stdio.h>
#include <time.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define PI25DT 3.141592653589793238462643
#define INTERVALS 100000000

int main(int argc, char **argv)
{
  long int i, intervals = INTERVALS;
  double x, dx, f, sum, pi;
  double time2, time4;
#ifdef _OPENMP
  double time1 = omp_get_wtime();
  time_t time3 = clock();
#else
  time_t time1 = clock();
  time_t time3 = clock();
#endif

  printf("Number of intervals: %ld\n", intervals);

  sum = 0.0;
  dx = 1.0 / (double) intervals;


 /*Calculate pi here*/
#pragma omp parallel for private(i,x) shared(dx) reduction(+:sum) 
  for (i = 0; i < intervals; i++) {
    x = (i + 0.5) * dx;
    sum += (4.0) / (1.0 + pow(x, 2.0));
  }

  pi = dx*sum;

#ifdef _OPENMP
  time2 = omp_get_wtime() - time1;
#else
  time2 = (clock() - time1) / (double) CLOCKS_PER_SEC;
#endif
time4 = (clock() - time3) / (double) CLOCKS_PER_SEC;


  printf("Computed PI %.24f\n", pi);
  printf("The true PI %.24f\n\n", PI25DT);
  printf("Elapsed time (s) = %.2lf\n", time2);
  printf("Clock() Elapsed time (s) = %.2lf\n", time4);

  return 0;
}
