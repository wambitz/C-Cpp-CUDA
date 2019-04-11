//////////////////////////////////////////////////////////////////////////
// Date: April 4th, 2019
// File: timing.cu
//////////////////////////////////////////////////////////////////////////

////////////////////////// DEPENDENCIES //////////////////////////////
 
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
// for random initialize
#include <stdlib.h>
#include <time.h>
// for memset
#include <cstring>

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

////////////////////////// GPU FUNCTIONS //////////////////////////////

__global__ void sum_array_gpu(int * a, int * b, int * c, int size)
{
    int gid = blockIdx.x * blockDim.x + threadIdx.x;
    if (gid < size)
    {
        c[gid] = a[gid] + b[gid];
        // printf("c[%d] -> %d = a[%d] -> %d + b[%d] -> %d \n", gid, c[gid], gid, a[gid], gid, b[gid]);
    }
}

int main()
{
    // Dimensions and sizes
    const int size = 1 << 25;;                  // number of all threads in grid
    const int block_size = 128;              // size block, each block has threads
    const int NO_BYTES = size * sizeof(int); // grid size un bytes    

    dim3 block(block_size);                  // 128 threads per block
    dim3 grid( (size/block.x) + 1);          // (10000 / 128) + 1  -> 79 blocks of 128 threas each 
                                             // this ensures we hace enough mem for all threads 

    // host pointers & mem alloc;
    int * h_a = (int *) malloc(NO_BYTES);
    int * h_b = (int *) malloc(NO_BYTES);
    int * gpu_result = (int *) malloc(NO_BYTES); // To compare results
    int * cpu_result = (int *) malloc(NO_BYTES);

    // device pointers & mem alloc
    int * d_a;
    int * d_b;
    int * d_c;

    cudaMalloc((void**)&d_a, NO_BYTES);
    cudaMalloc((void**)&d_b, NO_BYTES);
    cudaMalloc((void**)&d_c, NO_BYTES);

    // time variables
    clock_t cpu_start;
    clock_t gpu_start;
    clock_t htod_start;
    clock_t dtoh_start;

    clock_t cpu_end;
    clock_t gpu_end;
    clock_t htod_end;
    clock_t dtoh_end;

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

    // initialize result arrays to zero
    memset(gpu_result, 0, NO_BYTES);
    memset(cpu_result, 0, NO_BYTES);
    
    cpu_start = clock();
    sum_array_cpu(h_a, h_b, cpu_result, size);
    cpu_end = clock();

    // Memory transfer from host to device
    htod_start = clock();
    cudaMemcpy(d_a, h_a, NO_BYTES, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, NO_BYTES, cudaMemcpyHostToDevice);
    htod_end = clock();

    // grid = 79 blocks
    // block = 128 threads per block 
    gpu_start = clock();
    sum_array_gpu <<<grid, block>>> (d_a, d_b, d_c, size);

    // block execution until finish
    cudaDeviceSynchronize();
    gpu_end = clock();

    // Memory transfer from device to host
    dtoh_start = clock();
    cudaMemcpy(gpu_result, d_c, NO_BYTES, cudaMemcpyDeviceToHost);
    dtoh_end = clock();
    
    // array comparison
    compare_arrays(gpu_result, cpu_result, size);

    // Printing time differente / execution time
    printf("Sum array CPU execution time: %4.6f \n", (double) ((double)(cpu_end - cpu_start) / CLOCKS_PER_SEC));
    printf("Sum array GPU execution time: %4.6f \n", (double) ((double)(gpu_end - gpu_start) / CLOCKS_PER_SEC));
    printf("Host to Device Mem Transfer execution time: %4.6f \n", (double) ((double)(htod_end - htod_start) / CLOCKS_PER_SEC));
    printf("Device to Host Mem Transfer execution time: %4.6f \n", (double) ((double)(dtoh_end - dtoh_start) / CLOCKS_PER_SEC));
    printf("Sum array GPU total execution time: %4.6f \n", (double) ((double)(dtoh_end - htod_start) / CLOCKS_PER_SEC));
    
    // host release mem
    free(h_a);
    free(h_b);
    free(cpu_result);
    free(gpu_result);

    // device release mem
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    cudaDeviceReset();

    return 0;
}

