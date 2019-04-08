
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>


// ============================= [Arrays] ====================================

__global__ void unique_idx_calc_threadIdx(int * input)
{
	int tid = threadIdx.x;
	printf("threadIdx: %d, value: %d \n", tid, input[tid]);
}

// This function allows to calculate unique index for all elements no matter the block it belongs to
__global__ void unique_gid_calculation_2d(int * input)
{
	// For a grid of 4 blocks with 4 threads each
	int tid = threadIdx.x;					// tid	  -> Is the thread id within a block
	
	int block_offset = blockIdx.x * blockDim.x;	// offset -> blockId.x [0~3] * block dim.x = 4

	int row_offset = blockDim.x * gridDim.x * blockIdx.y;
	 
	int gid = tid + row_offset + block_offset; // gid    -> id in block + row_offset + block_offset
	printf("blockIdx.x: %d, blockIdx.y: %d, threadIdx.x: %d, gid: %d, value: %d \n",
		blockIdx.x, blockIdx.y, tid, gid, input[gid]);
}

int main()
{
	int array_size = 16;
	int array_byte_size = sizeof(int) * array_size;
	int h_data[] = { 23, 9, 4, 53, 65, 12, 1, 33, 87, 45, 26, 12, 342, 56, 44, 99 };

	for (int i = 0; i < array_size; i++)
	{
		printf("%d ", h_data[i]);
	}
	printf("\n\n");

	int * d_data;
	cudaMalloc((void**)&d_data, array_byte_size);
	cudaMemcpy(d_data, h_data, array_byte_size, cudaMemcpyHostToDevice);

	dim3 block(4);
	dim3 grid(2, 2);

	unique_gid_calculation_2d << < grid, block >> > (d_data);
	// unique_idx_calc_threadIdx << < grid, block >> > (d_data);
	cudaDeviceSynchronize();

	cudaDeviceReset();

	return 0;
}

// =========================== [Hello World] =================================

//__global__ void hello_cuda()
//{
//	printf("Hello CUDA World\n");
//}

//__global__ void print_details()
//{
//	printf("blockIdx.x: %d, blockIdx.y: %d, blockIdx.z: %d, blockDim.x: %d, blockDim.y: %d, blockDim.z: %d, gridDim.x: %d, gridDim.y: %d, gridDim.z: %d\n",
//		threadIdx.x, threadIdx.y, threadIdx.z, blockDim.x, blockDim.y, blockDim.z, gridDim.x, gridDim.y, gridDim.z);
//}

//int main()
//{
//	int nx, ny, nz;
//	nx = 4;
//	ny = 4;
//	nz = 4;
//
//	dim3 block(2, 2, 2); 
//	dim3 grid(nx / block.x, ny / block.y, nz / block.z);  
//	print_details << < grid, block >> > ();
//	cudaDeviceSynchronize();
//
//	cudaDeviceReset();
//
//	return 0;
//}
