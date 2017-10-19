#include <cuda_runtime_api.h>
#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __CUDACC__ 
#define __CUDACC__
#endif
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cuda.h>
#include <device_functions.h>
#include <cuda_runtime_api.h>


static void HandleError(cudaError_t err, const char *file, int line) {
	if (err != cudaSuccess) {
		printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
		exit(EXIT_FAILURE);
	}
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

#define imin(a,b) (a<b?a:b)

const int N = 33 * 1024;
const int threadsPerBlock = 256;
const int blocksPerGrid = imin(32, (N + threadsPerBlock - 1) / threadsPerBlock);

__global__ void dot(float *a, float *b, float *c)
{
	__shared__ float cache[threadsPerBlock];
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	int cacheIndex = threadIdx.x;
	float temp = 0;
	int stride;
	while (tid < N) {
		temp += a[tid] * b[tid];
		tid += blockDim.x * gridDim.x;
	}
	cache[cacheIndex] = temp;
	__syncthreads();

	for (stride = (threadsPerBlock >> 1); stride > 0; stride >>= 1) {
		if (cacheIndex < stride)
			cache[cacheIndex] += cache[cacheIndex + stride];

		__syncthreads();
	}

	c[blockIdx.x] = cache[0];
}

int main()
{
	float   *a, *b, c, *partial_c;
	float   *dev_a, *dev_b, *dev_partial_c;

	// allocate memory on the cpu side
	a = (float*)malloc(N * sizeof(float));
	b = (float*)malloc(N * sizeof(float));
	partial_c = (float*)malloc(blocksPerGrid * sizeof(float));

	// allocate the memory on the GPU
	HANDLE_ERROR(cudaMalloc((void**)&dev_a, N * sizeof(float)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_b, N * sizeof(float)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_partial_c, blocksPerGrid * sizeof(float)));

	// fill in the host memory with data
	for (int i = 0; i<N; i++) {
		a[i] = i; b[i] = i * 2;
	}

	// copy the arrays 'a' and 'b' to the GPU
	HANDLE_ERROR(cudaMemcpy(dev_a, a, N * sizeof(float), cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_b, b, N * sizeof(float), cudaMemcpyHostToDevice));

	dot << <blocksPerGrid, threadsPerBlock >> >(dev_a, dev_b, dev_partial_c);

	// copy the array 'c' back from the GPU to the CPU
	HANDLE_ERROR(cudaMemcpy(partial_c, dev_partial_c, blocksPerGrid * sizeof(float),cudaMemcpyDeviceToHost));

	// finish up on the CPU side
	c = 0;
	for (int i = 0; i<blocksPerGrid; i++) {
		c += partial_c[i];
	}

#define sum_squares(x)  (x*(x+1)*(2*x+1)/6)
	printf("Does GPU value %.6g = %.6g?\n", c,
		2 * sum_squares((float)(N - 1)));

	// free memory on the gpu side
	HANDLE_ERROR(cudaFree(dev_a));
	HANDLE_ERROR(cudaFree(dev_b));
	HANDLE_ERROR(cudaFree(dev_partial_c));

	// free memory on the cpu side
	free(a);
	free(b);
	free(partial_c);

}

