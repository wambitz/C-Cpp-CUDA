#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "curand.h"

#include <ctime>
#include <cstdio>
#include <iostream>

using namespace std;


__global__ void addTen(float * d, int count) 
{
    int threadsPerBlock = blockDim.x * blockDim.y * blockDim.z;
    int threadPosInBlock = threadIdx.x + blockDim.x * threadIdx.y + threadIdx.z * blockDim.x * blockDim.y;
    int blockPostInGrid = blockIdx.x + gridDim.x * blockIdx.y + gridDim.x * gridDim.y * blockIdx.z;
    
    // int blockOffset = threadsPerBlock * blockIdx.x
    // int rowOffset = threadsPerBlock * gridDim.x *  blockIdx.y;
    
    int tid = blockPostInGrid * threadsPerBlock + threadPosInBlock;
    
    if (tid < count)
    {
        d[tid] += 10;
    }
    
}

int main(int argc, char const *argv[])
{
    curandGenerator_t gen;
    curandCreateGenerator(&gen, CURAND_RNG_PSEUDO_MTGP32);
    curandSetPseudoRandomGeneratorSeed(gen, time(0));

    const int count = 123456;
    const int size = count * sizeof(float);

    float * d;
    float h[count];

    cudaMalloc((void**)&d, size);
    curandGenerateUniform(gen, d, count);

    dim3 block(8, 8, 8);
    dim3 grid(16, 16);

    addTen<<<grid, block>>>(d, count);  

    cudaMemcpy(h, d, size, cudaMemcpyDeviceToHost);

    cudaFree(d);
    
    for (int i = 0; i < 100; i++)   
    {
        cout << h[i] << endl;
    }

    return 0;
}

