#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>


using namespace std;

__global__ void sumSingleBlock(int * d) 
{
    int tid = threadIdx.x;

    // tc - numer of participating threads;
    for (int tc = blockDim.x, stepSize = 1; tc > 0; tc >>=1, stepSize <<= 1)
    {
        //thread must be write
        if (tid < tc)
        {
            int pa = tid * stepSize * 2;
            int pb = pa + stepSize;
            d[pa] += d[pb];
        }
    }
}


int main(int argc, char const *argv[])
{
    const int count = 512;
    const int size = count * sizeof(int);
    int result;

    int h[count];
    for (int i = 0; i < count; i++)
    {
        h[i] = i + 1;
    }

    int * d; 
    cudaMalloc(&d, size);
    cudaMemcpy(d, h, size, cudaMemcpyHostToDevice);

    sumSingleBlock<<<1, count/2>>>(d);

    cudaMemcpy(&result, d, size, cudaMemcpyDeviceToHost);
    
    cout << "sum is " << result << endl;

    cudaFree(d);
    
    return 0;
}