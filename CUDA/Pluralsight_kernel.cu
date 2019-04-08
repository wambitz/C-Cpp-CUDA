#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "stdio.h"

__global__ void addArrays(int * a, int * b, int * c)
{
	int i = threadIdx.x;
	c[i] = a[i] + b[i];
}

int main()
{
	const int count = 5;
	const int size = count * sizeof(int);

	int h_a[] = { 1, 2, 3, 4, 5 };
	int h_b[] = { 10, 20, 30, 40, 50 };
	int h_c[count];

	int * d_a;
	int * d_b;
	int * d_c;

	cudaMalloc(&d_a, size);
	cudaMalloc(&d_b, size);
	cudaMalloc(&d_c, size);

	cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);
	// cudaMemcpy(d_c, h_c, size, cudaMemcpyHostToDevice);

	addArrays << <1, count >> >(d_a, d_b, d_c);

	cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);
		
	for (int i = 0; i < count; i++)
	{
		printf("%d ", h_c[i]);
	}
	return 0;
}
