#include <iostream>
#include <stdio.h>
#include <math.h>


__global__ void cuPi(float *sum, int nbin, float step)
{
  
    // Write your pi calculation kernel here
    return;
}


int main(void)
{
    int REAL_PI = 3.141592653589793238462643383;
    int NBINS = 10; // modify this to achieve better performance
    int STEP = 5;   // modify this to achieve better performance
    float* pi;

    cudaMallocManaged(&pi, sizeof(float));

    //   Calculate Pi

    cuPi<<<1, 1>>>(pi, NBINS, STEP);

    // Wait for GPU to finish before accessing on host
    cudaDeviceSynchronize();

    printf("Pi calculated as %f\n", *pi);

    float acc = REAL_PI - *pi;
    printf("Accuracy of Pi calculation %f\n", acc);
    
    // Free memory
    cudaFree(pi);
    
    return 0;
}