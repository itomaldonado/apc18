#include <iostream>
#include <stdio.h>
#include <math.h>

// kernels transpose a tile of TILE_DIM x TILE_DIM elements
// using a TILE_DIM x BLOCK_ROWS thread block, so that each thread
// transposes TILE_DIM/BLOCK_ROWS elements.
// TILE_DIM must be an integral multiple of BLOCK_ROWS
#define TILE_DIM 32
#define BLOCK_ROWS 8


__global__ void cuTranspose(int rows, int cols, const float *input, float *output) {

  //int x = blockIdx.x * TILE_DIM + threadIdx.x;
  //int y = blockIdx.y * TILE_DIM + threadIdx.y;
  //int width = gridDim.x * TILE_DIM;

  int tile_size = blockDim.x ;
  int column = tile_size * blockIdx.x + threadIdx.x;
  int row = tile_size * blockIdx.y + threadIdx.y;
  if(column < cols && row < rows){
    output[column*cols + row] = input[column + row*rows];
  }

  /*
  for (int j = 0; j < TILE_DIM; j+= BLOCK_ROWS) {
    output[x*width + (y+j)] = input[(y+j)*width + x];
  }
  */

  return;
}

int check(int nrows, int ncols, float* input, float* output) {
    for (int i = 0; i < nrows; i++){
        for(int j = 0; j < ncols; j++) {
            if (input[i*ncols + j] != output[j*ncols + i]) {
                printf("Input at (%i, %i) not equal to output at (%i, %i) with %f != %f\n", i, j, j, i, input[i*ncols + j], output[j*ncols + i]);
                return 0;
            }
        }
    }
    return 1;
}

int main(void)
{
  int r = 10000; // rows
  int c = 10000;  // columns
  int N = r*c;   // total matrix entries.

  float *input, *output;

  dim3 dimGrid(r/TILE_DIM, c/TILE_DIM, 1);
  dim3 dimBlock(TILE_DIM, BLOCK_ROWS, 1);

  // Allocate Unified Memory – accessible from CPU or GPU
  cudaMallocManaged(&input, N*sizeof(float));
  cudaMallocManaged(&output, N*sizeof(float));

  // initialize input and output matrices on the host
  for (int i = 0; i < r; i++) {
      for(int j = i; j < c; j++) {
        input[i*c + j] = (float)r*i + r*1.0f;
        output[i*c + j] = 5.0f;
      }

  }

  // Transpose the matrix
  printf("Before\n");
  cuTranspose<<<dimGrid, dimBlock>>>(r, c, input, output);
  printf("After\n");

  // Wait for GPU to finish before accessing on host
  cudaDeviceSynchronize();

  if (!check(r, c, input, output)) {
      printf("Matrix entries not equal\n"); 
  } else {
      printf("Matrix transpose successful\n");
  }

  // Free memory
  cudaFree(input);
  cudaFree(output);
  
  return 0;
}
