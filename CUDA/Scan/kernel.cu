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
#include <time.h>
#include <Math.h>

static void HandleError(cudaError_t err, const char *file, int line) {
	if (err != cudaSuccess) {
		printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
		exit(EXIT_FAILURE);
	}
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

const int N = 1024;
const int threadsPerBlock = 1024;
const int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

/*__global__ void scan_work_inefficient(long * dev_a, long * dev_output)
{
	__shared__ long SMem[threadsPerBlock];
	int tx = threadIdx.x;
	int stride;
	int temp;
	SMem[tx] = dev_a[tx];

	for (stride = 1; stride <= tx; stride *= 2) {

		__syncthreads();
		 temp = SMem[tx - stride];
		__syncthreads();

		SMem[tx] += temp;
	}
	
	dev_output[tx] = SMem[tx];
}

__global__ void scan_work_efficient(long * dev_a, long * dev_output )
{
	__shared__ long SMem[threadsPerBlock];
	int tx = threadIdx.x;
	int stride,index;

	SMem[2*tx] = dev_a[2*tx];
	SMem[2*tx+1] = dev_a[2*tx+1];

	// Reduction
	for(stride = 1 ; stride <= threadsPerBlock/2 ; stride *= 2 ){
		index = (threadIdx.x+1)*stride*2-1;
		if( index < threadsPerBlock )
			SMem[index] += SMem[index-stride];
		__syncthreads();
	}

	// Post reduction
	for(stride = threadsPerBlock/4 ; stride >0 ; stride /= 2 ){
		index = (threadIdx.x+1)*stride*2-1;
		if( index+stride < threadsPerBlock )
			SMem[index+stride] += SMem[index];
		__syncthreads();
	}

	dev_output[2*tx] = SMem[2*tx];
	dev_output[2*tx+1] = SMem[2*tx+1];
}*/

__global__ void scan_work_inefficient(long * dev_a, long * dev_output)
{
	__shared__ long SMem[threadsPerBlock];
	int tx = threadIdx.x;
	int stride;
	long temp = 0;
	SMem[tx] = dev_a[tx];

	for (stride = 1; stride <= tx; stride <<= 1) {

		__syncthreads();	
		if (tx >= stride)
			temp = SMem[tx - stride];
		__syncthreads(); 

		SMem[tx] += temp;
	}

	dev_output[tx] = SMem[tx];
}

__global__ void scan_work_efficient(long * dev_a, long * dev_output)
{
	__shared__ long SMem[threadsPerBlock];
	int tx = threadIdx.x;
	int index,stride;
	SMem[2 * tx] = dev_a[2 * tx];
	SMem[2 * tx + 1] = dev_a[2 * tx + 1];

	// Reduction
	for (stride = 1; stride < threadsPerBlock; stride <<= 1) {
		index = (threadIdx.x + 1)*stride * 2 - 1;
		if (index < threadsPerBlock)
			SMem[index] += SMem[index - stride];

		__syncthreads();
	}
	// Post reduction
	for (stride = (threadsPerBlock >> 2); stride > 0; stride >>= 1) {
		index = (threadIdx.x + 1)*stride * 2 - 1;
		if (index + stride < threadsPerBlock)
			SMem[index + stride] += SMem[index];

		__syncthreads();
	}

	dev_output[2 * tx] = SMem[2 * tx];
	dev_output[2 * tx + 1] = SMem[2 * tx + 1];
}

int main()
{
    long   *a, *output;
    long   *dev_a, *dev_output;

    // allocate memory on the cpu side
    a = (long*)malloc( N*sizeof(long) );
    output = (long*)malloc( N*sizeof(long) );

    // allocate the memory on the GPU
    HANDLE_ERROR( cudaMalloc( (void**)&dev_a, N*sizeof(long) ) );
    HANDLE_ERROR( cudaMalloc( (void**)&dev_output, N*sizeof(long) ) );

    // fill in the host memory with data
    for (int i=0; i<N; i++) {
        a[i] = (rand()%10);
    }
    printf("blocksPerGrid:%d , threadsPerBLock:%d\n", blocksPerGrid, threadsPerBlock );

    // copy the arrays 'a' and 'b' to the GPU
    HANDLE_ERROR( cudaMemcpy( dev_a, a, N*sizeof(long), cudaMemcpyHostToDevice ) );
  
    clock_t start = clock();
	//scan_work_inefficient <<<blocksPerGrid,threadsPerBlock>>>( dev_a, dev_output );
	scan_work_efficient << <blocksPerGrid, threadsPerBlock / 2 >> >(dev_a, dev_output);

    HANDLE_ERROR( cudaDeviceSynchronize());
    clock_t end = clock();

    printf(" kernel execution time: %lf sec\n", (double)(end-start)/(double)CLOCKS_PER_SEC );

    // copy the array 'c' back from the GPU to the CPU
    HANDLE_ERROR( cudaMemcpy( output, dev_output, N*sizeof(long), cudaMemcpyDeviceToHost ) );

	long d = 0;
	for (int i = 0; i<N; i++) {
		d += a[i];
		if (d != output[i]) {
			printf("i=%d, d:%d and output:%d\n", i, d, output[i]);
			printf("Error!"); goto CLEANUP;
		}
	}
	printf("PASS!\n");

CLEANUP:
	// free memory on the gpu side
	HANDLE_ERROR(cudaFree(dev_a));
	HANDLE_ERROR(cudaFree(dev_output));

	// free memory on the cpu side
	free(a);
	free(output);
}


