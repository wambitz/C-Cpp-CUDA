#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

// This function allows to calculate unique index for all elements no matter the block it belongs to
__global__ void unique_gid_calculation_3d(int * data)
{
	// For a grid of 4 blocks with 4 threads each
	int tid = threadIdx.x + blockDim.x * threadIdx.y + threadIdx.z * blockDim.x * blockDim.y;	// tid	  -> Is the thread id within a block

	int num_threads_in_block = blockDim.x * blockDim.y * blockDim.z;
	int block_offset = blockIdx.x * num_threads_in_block;	// offset -> blockId.x [0~3] * block dim.x = 4

	int num_threads_in_row =  num_threads_in_block * gridDim.x;
	int row_offset = num_threads_in_row * blockIdx.y;
	 
    int gid = tid + row_offset + block_offset; // gid    -> id in block + row_offset + block_offset
    
    printf("blockIdx.x: %d, blockIdx.y: %d, blockIdx.z: %d, threadIdx.x: %d, gid: %d - data: %d \n",
            blockIdx.x, blockIdx.y, blockIdx.z, tid, gid, data[gid]);

}

int main()
{
    // Size
    int size = 64;
    int size_bytes = size * sizeof(int);
    
    // Grid dimensions 
    dim3 block(2, 2, 2);
    dim3 grid(2, 2, 1);

    // Memory allocation
    int * h_input = (int *) malloc(size_bytes);
    int * d_input;

    cudaMalloc((void**)&d_input, size_bytes);

    // Rand value assigment
    for (int i = 0; i < size; i++)
    {
        h_input[i] = (int) (rand() & 0xff);
    }

    // Pass host array values to device
    cudaMemcpy(d_input, h_input, size_bytes, cudaMemcpyHostToDevice);

    // Call kernel
    unique_gid_calculation_3d << <grid, block>> > (d_input);

    // Wait for kernel to finish
    cudaDeviceSynchronize();
    
    // Release memory
    free(h_input);
    cudaFree(d_input);

    cudaDeviceReset();

    return 0;
}