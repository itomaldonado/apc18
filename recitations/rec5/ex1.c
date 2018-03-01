#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

  int me, nprocs;

  /* Initialize MPI environment */
  MPI_Init(&argc, &argv) ;

  /* Write MPI Code Here */


  /* Finalize MPI environment */
  MPI_Finalize() ;

}