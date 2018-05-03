#include <iostream>
#include <stdio.h>
#include <math.h>

// kernels transpose a tile of TILE_DIM x TILE_DIM elements
// using a TILE_DIM x BLOCK_ROWS thread block, so that each thread
// transposes TILE_DIM/BLOCK_ROWS elements.
// TILE_DIM must be an integral multiple of BLOCK_ROWS
#define SIZE 10016
#define TILE_DIM 32
#define BLOCK_ROWS 8


__global__ void cuTranspose(int rows, int cols, const float *input, float *output) {

  __shared__ float tile[TILE_DIM][TILE_DIM];
  
  int x = blockIdx.x * TILE_DIM + threadIdx.x;
  int y = blockIdx.y * TILE_DIM + threadIdx.y;
  int index_in = x + (y)*rows;
  x = blockIdx.y * TILE_DIM + threadIdx.x;
  y = blockIdx.x * TILE_DIM + threadIdx.y;
  int index_out = x + (y)*cols;
  
  for (int i=0; i < TILE_DIM; i += BLOCK_ROWS) {
    tile[threadIdx.y+i][threadIdx.x] = input[index_in+i*rows];
  }
  __syncthreads();

  for (int i=0; i < TILE_DIM; i += BLOCK_ROWS) {
    output[index_out + i*cols] = tile[threadIdx.x][threadIdx.y + i];
  }

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
  int r = SIZE;  // rows
  int c = SIZE;  // columns
  int N = r*c;    // total matrix entries.

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
  cuTranspose<<<dimGrid, dimBlock>>>(r, c, input, output);

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
