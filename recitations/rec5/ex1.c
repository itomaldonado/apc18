#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

  int me, nprocs;

  /* Initialize MPI environment */
  MPI_Init(&argc, &argv) ;

  /* Write MPI Code Here */
  MPI_Comm_rank( MPI_COMM_WORLD, &me ); 
  MPI_Comm_size( MPI_COMM_WORLD, &nprocs ); 
  printf("hello world, I am task %d from total %d\n", me, nprocs );
  
  /* Finalize MPI environment */
  MPI_Finalize();
  return 0;
}