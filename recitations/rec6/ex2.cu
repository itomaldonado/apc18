#include <iostream>
#include <stdio.h>
#include <math.h>


__global__ void cuTranspose(int rows, int cols, float *input, float *output)
{
  
    // Write your transpose kernel here
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

  // Allocate Unified Memory – accessible from CPU or GPU
  cudaMallocManaged(&input, N*sizeof(float));
  cudaMallocManaged(&output, N*sizeof(float));

  // initialize input and output matrices on the host
  for (int i = 0; i < r; i++) {
      for(int j = i; j < c; j++) {
        input[i*c + j] = (float)nrows*i + r*1.0f;
        output[i*c + j] = 5.0f;
      }

  }

//   Transpose the matrix
  cuTranspose<<<1, 1>>>(r, c, input, output);

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
