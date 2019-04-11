#include "cuda_runtime.h"
#include "device_launch_parameters.h"
// #include "common.h"

#include <stdio.h>
// for random initialize
#include <stdlib.h>
#include <time.h>
// for memset
#include <cstring>

__global__ void sum_array_gpu(int * a, int * b, int * c, int size)
{
    int gid = blockIdx.x * blockDim.x + threadIdx.x;
    if (gid < size)
    {
        c[gid] = a[gid] + b[gid];
        // printf("c[%d] -> %d = a[%d] -> %d + b[%d] -> %d \n", gid, c[gid], gid, a[gid], gid, b[gid]);
    }
}

void check_cuda_error(cudaError error)
{
    if (error != cudaSuccess)
    {
        fprintf(stderr, "Error: %s \n", cudaGetErrorString(error));
    }
}

void sum_array_cpu(int * a, int * b, int * c, int size)
{
    // printf("CPU values \n");
    for (int i = 0; i < size; i++)
    {
        c[i] = a[i] + b[i];
        // printf("c[%d] -> %d = a[%d] -> %d + b[%d] -> %d \n", i, c[i], i, a[i], i, b[i]);
    }
    //printf("\n");
}

// compare arrays
void compare_arrays(int * a, int * b, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (a[i] != b[i])
        {
            printf("Arrays are different, a[%d] -> %d != b[%d] -> %d \n", i, a[i], i, b[i]);
            return;
        }
    }
    printf("Arrays are  the same \n");
}

int main()
{
    const int size = 1 << 25;                  // number of all threads in grid
    const int block_size = 1024;              // size block, each block has threads
    const int NO_BYTES = size * sizeof(int); // grid size un bytes    



    dim3 block(block_size);                  // 128 threads per block
    dim3 grid( (size/block.x) + 1);      // (10000 / 128) + 1  -> 79 blocks of 128 threas each 
                                             // this ensures we hace enough mem for all threads 

    // host pointers & mem alloc;
    int * h_a = (int *) malloc(NO_BYTES);
    int * h_b = (int *) malloc(NO_BYTES);
    int * h_c = (int *) malloc(NO_BYTES); // To compare results
    int * gpu_result = (int *) malloc(NO_BYTES);

    // device pointers & mem alloc
    int * d_a;
    int * d_b;
    int * d_c;

    check_cuda_error(cudaMalloc((void**)&d_a, NO_BYTES));
    cudaMalloc((void**)&d_b, NO_BYTES);
    cudaMalloc((void**)&d_c, NO_BYTES);

    // initialize host pointer
    time_t t;
    srand( (unsigned) time(&t) );
    for (int i = 0; i < size; i++)
    {
        h_a[i] = (int) (rand() & 0xff);
    }

    for (int i = 0; i < size; i++)
    {
        h_b[i] = (int) (rand() & 0xff);
    }

    memset(gpu_result, 0, NO_BYTES);

    // Memory transfer from host to device
    cudaMemcpy(d_a, h_a, NO_BYTES, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, NO_BYTES, cudaMemcpyHostToDevice);

    // grid = 79 blocks
    // block = 128 threads per block 
    sum_array_gpu <<<grid, block>>> (d_a, d_b, d_c, size);
    sum_array_cpu(h_a, h_b, h_c, size);
    // block execution until finish
    cudaDeviceSynchronize();

    // Memory transfer from device to host
    cudaMemcpy(gpu_result, d_c, NO_BYTES, cudaMemcpyDeviceToHost);
    
    // array comparison
    compare_arrays(gpu_result, h_c, size);
    
    // host release mem
    free(h_a);
    free(h_b);
    free(h_c);
    free(gpu_result);

    // device release mem
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    cudaDeviceReset();

    return 0;
}

