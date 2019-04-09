#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

__global__ void mem_trs_test(int * input)
{
    int gid = blockIdx.x * blockDim.x + threadIdx.x;
    printf("tid: %d, gid: %d, value: %d \n", threadIdx.x, gid, input[gid]);
}

int main()
{
    int size = 128; // array size
    int byte_size = size * sizeof(int); // complete array byte size

    int * h_input;  // host memory pointer
    h_input = (int *) malloc(byte_size); // host memory allocation

    time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < size; i++)
    {
        h_input[i] = (int) (rand() & 0xff); // Fill host array with random values
    }

    int * d_input;  // device memory pointer
    cudaMalloc((void**)&d_input, byte_size); // device memory allocation

    cudaMemcpy(d_input, h_input, byte_size, cudaMemcpyHostToDevice); // memory cpy from host to device

    dim3 block(64); // 64 threads in x dimesion for each block
    dim3 grid(2);   // 2 blocks in x for whole grid

    mem_trs_test << < grid, block >> >(d_input);
    
    cudaDeviceSynchronize();    // wait for device to finish kernel execution 

    // cudaMemcpy(h_input, d_input, byte_size, cudaMemcpyDeviceToHost); // memory cpy from device to host
    
    // Resource release host & dev
    free(h_input);
    cudaFree(d_input);

    cudaDeviceReset();

    return 0;
}