#include <cuda_runtime_api.h>
#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __CUDACC__ 
#define __CUDACC__
#endif

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <device_functions.h>
#include <time.h>
#include <math.h>

const int N = 1024;
const int threadsPerBlock = 1024;
const int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

static void HandleError(cudaError_t err, const char *file, int line) {
	if (err != cudaSuccess) {
		printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
		exit(EXIT_FAILURE);
	}
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

void verify2D(float * N, float  * P, float * mask, int width, int height, int mask_width);

#define WIDTH 300
#define HEIGHT 200
#define MASK_WIDTH 5

#define O_TILE_WIDTH 12
#define BLOCK_WIDTH (O_TILE_WIDTH + 4)

__global__ void Conv2D(float * N, float * P, float * Mask, int width, int height, int mask_width)
{
	float output = 0.0f;
	int tx = threadIdx.x; int ty = threadIdx.y;
	int row_o = blockIdx.y*O_TILE_WIDTH + threadIdx.y;
	int col_o = blockIdx.x*O_TILE_WIDTH + threadIdx.x;
	int row_i = row_o - 2;
	int col_i = col_o - 2;
	int i, j;
	int mask_i = 0, mask_j = 0;
	__shared__ float Ns[BLOCK_WIDTH][BLOCK_WIDTH];

	// All threads participate in loading data to Ns[][]
	if ((0 < row_i && row_i < height) && (0 < col_i && col_i < width))
		Ns[ty][tx] = N[width*row_i + col_i];
	else
		Ns[ty][tx] = 0.0f;

	__syncthreads();

	// Some threads participate in calculating P[]. Be careful around the boundaries of Matrix!
	if ((row_o < height && col_o < width) && (ty < O_TILE_WIDTH && tx < O_TILE_WIDTH)) {
		for (i = 0; i < mask_width ; i++) {
			mask_j = 0;
			for (j = 0; j < mask_width ; j++) {
				output += Mask[i*mask_width + j] * Ns[i+ty][j+tx];
			}
		}
		P[row_o*WIDTH + col_o] = output;
	}
}


int main()
{
	float *N, *P, *Mask;
	float *dev_N, *dev_P, *dev_Mask;

	N = (float*)malloc(sizeof(float)*WIDTH*HEIGHT);
	P = (float*)malloc(sizeof(float)*WIDTH*HEIGHT);
	Mask = (float*)malloc(sizeof(float)*MASK_WIDTH*MASK_WIDTH);

	for (int i = 0; i < WIDTH*HEIGHT; i++) { N[i] = (rand() % 100) / 100.00; }
	for (int i = 0; i<MASK_WIDTH*MASK_WIDTH; i++) { Mask[i] = (rand() % 100) / 100.00; }

	// Add vectors in parallel.
	HANDLE_ERROR(cudaMalloc((void**)&dev_N, WIDTH * HEIGHT * sizeof(float)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_P, WIDTH * HEIGHT * sizeof(float)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_Mask, MASK_WIDTH * MASK_WIDTH * sizeof(float)));
	HANDLE_ERROR(cudaMemcpy(dev_N, N, WIDTH * HEIGHT * sizeof(float), cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_Mask, Mask, MASK_WIDTH * MASK_WIDTH * sizeof(float), cudaMemcpyHostToDevice));

	// Launch a kernel on the GPU with one thread for each element.
	dim3 dimBlock(BLOCK_WIDTH, BLOCK_WIDTH, 1);
	dim3 dimGrid((WIDTH - 1) / O_TILE_WIDTH + 1, (HEIGHT - 1) / O_TILE_WIDTH + 1, 1);
	Conv2D << <dimGrid, dimBlock >> >(dev_N, dev_P, dev_Mask, WIDTH, HEIGHT, MASK_WIDTH);
	HANDLE_ERROR(cudaDeviceSynchronize());

	// Copy output vector from GPU buffer to host memory.
	HANDLE_ERROR(cudaMemcpy(P, dev_P, WIDTH * HEIGHT * sizeof(float), cudaMemcpyDeviceToHost));
	verify2D(N, P, Mask, WIDTH, HEIGHT, MASK_WIDTH);

	cudaFree(dev_N);     cudaFree(dev_P); cudaFree(dev_Mask);
	free(N); free(P); free(Mask);
	return 0;
}

void verify2D(float * N, float  * P, float * mask, int width, int height, int mask_width) {
	const float relativeTolerance = 1e-6;
	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			float sum = 0.0f;
			for (int row_m = 0; row_m < mask_width; ++row_m) {
				for (int col_m = 0; col_m < mask_width; ++col_m) {
					int row_N = row + row_m - (int)(mask_width / 2);
					int col_N = col + col_m - (int)(mask_width / 2);
					if (col_N >= 0 && col_N < width && row_N >= 0 && row_N<height) {
						sum += mask[row_m*mask_width + col_m] * N[row_N*width + col_N];
					}
				}
			}
			float relativeError = (sum - P[row*width + col]) / sum;
			if (relativeError > relativeTolerance || relativeError < -relativeTolerance) {
				printf("TEST FAILED\n");
				exit(0);
			}
		}
	}
	printf("TEST PASSED\n\n");
}
