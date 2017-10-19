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

#define LEN_M (2*1024+3)
#define LEN_N (2*1024+3)
#define LEN_K (1*1024+3)
#define TILE_WIDTH 32

__global__ void MatrixMulOnDevice(int m, int n, int k, float * A, float * B, float * C) {
	int col = threadIdx.x + blockIdx.x * blockDim.x;
	int row = threadIdx.y + blockIdx.y * blockDim.y;

	if (col < LEN_K && row < LEN_M)
		for (int i = 0; i < n; ++i)
			C[row * k + col] += A[row * n + i] * B[col + i*k];
}

__global__ void TiledMatrixMulKernel(int m, int n, int k, float* A, float* B, float* C)
{
	__shared__ float ds_A[TILE_WIDTH][TILE_WIDTH];
	__shared__ float ds_B[TILE_WIDTH][TILE_WIDTH];

	int bx = blockIdx.x; int by = blockIdx.y;
	int tx = threadIdx.x; int ty = threadIdx.y;

	int Row = by * blockDim.y + ty;
	int Col = bx * blockDim.x + tx;

	float Cvalue = 0;
	for (int t = 0; t < n / TILE_WIDTH; ++t) {	// iterate over phases
												// load A and B tiles into shared memory 
		if ((Row < m) && (t*TILE_WIDTH + tx < n))
			ds_A[ty][tx] = A[Row*n + (t*TILE_WIDTH + tx)];
		else
			ds_A[ty][tx] = 0;

		if ((t*TILE_WIDTH + ty < n) && (Col < k))
			ds_B[ty][tx] = B[(t*TILE_WIDTH + ty)*k + Col];
		else
			ds_B[ty][tx] = 0;

		__syncthreads();												// 무거운 함수

																		// compute Cvalue based on ds_A[][] and ds_B[][]

		for (int i = 0; i < TILE_WIDTH; i++)
			Cvalue += ds_A[ty][i] * ds_B[i][tx];

		__syncthreads();
	}

	if (Row < m && Col < k)
		C[Row*k + Col] = Cvalue;
}

void MatrixMulOnHost(int m, int n, int k, float* A, float* B, float* C)
{
	for (int Row = 0; Row < m; ++Row)
		for (int Col = 0; Col < k; ++Col) {
			float sum = 0;

			for (int i = 0; i < n; ++i) {
				float a = A[Row * n + i];
				float b = B[Col + i*k];
				sum += a * b;
			}

			C[Row * k + Col] = sum;
		}
}

int main()
{
	clock_t start, stop, start1, stop1;
	// Allocate and initialize the matrices A, B, C
	float * A, *B, *C, *D;

	A = (float*)malloc(LEN_M*LEN_N * sizeof(float));
	B = (float*)malloc(LEN_N*LEN_K * sizeof(float));
	C = (float*)malloc(LEN_M*LEN_K * sizeof(float));
	D = (float*)malloc(LEN_M*LEN_K * sizeof(float));

	for (int i = 0; i<LEN_M*LEN_N; i++) A[i] = i % 3;
	for (int i = 0; i<LEN_N*LEN_K; i++) B[i] = i % 4;
	for (int i = 0; i<LEN_M*LEN_K; i++) C[i] = 0.0;
	for (int i = 0; i<LEN_M*LEN_K; i++) D[i] = 0.0;

	// I/O to read the input matrices A and B
	float * dev_A, *dev_B, *dev_C;
	cudaMalloc((void**)&dev_A, LEN_M*LEN_N * sizeof(float));
	cudaMalloc((void**)&dev_B, LEN_N*LEN_K * sizeof(float));
	cudaMalloc((void**)&dev_C, LEN_M*LEN_K * sizeof(float));

	cudaMemcpy(dev_A, A, LEN_M*LEN_N * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_B, B, LEN_N*LEN_K * sizeof(float), cudaMemcpyHostToDevice);

	// A*B on the device
	dim3 dimGrid((LEN_K - 1) / TILE_WIDTH + 1, (LEN_M - 1) / TILE_WIDTH + 1);
	dim3 dimBlock(TILE_WIDTH, TILE_WIDTH);

	start = clock();
	MatrixMulOnDevice << <dimGrid, dimBlock >> >(LEN_M, LEN_N, LEN_K, dev_A, dev_B, dev_C);
	cudaDeviceSynchronize();
	stop = clock();

	printf("Run time(no tile) : : %lf sec\n", (float)(stop - start) / (float)CLOCKS_PER_SEC);


	start1 = clock();
	TiledMatrixMulKernel << <dimGrid, dimBlock >> >(LEN_M, LEN_N, LEN_K, dev_A, dev_B, dev_C);
	cudaDeviceSynchronize();
	stop1 = clock();

	printf("Run time(tile) : : %lf sec\n", (float)(stop1 - start1) / (float)CLOCKS_PER_SEC);

	// I/O to write the output matrix C
	cudaMemcpy(C, dev_C, LEN_M*LEN_K * sizeof(float), cudaMemcpyDeviceToHost);

	printf("C:");
	for (int i = 0; i<LEN_M*LEN_K; i++) printf(" %6.1f", C[i]);
	printf("\n");
	printf("\n");

	MatrixMulOnHost(LEN_M, LEN_N, LEN_K, A, B, D);

	printf("D:");
	for (int i = 0; i<LEN_M*LEN_K; i++) printf(" %6.1f", D[i]);
	printf("\n");

	// Free matrices A, B, C
	cudaFree(dev_A);
	cudaFree(dev_B);
	cudaFree(dev_C);

	free(A);
	free(B);
	free(C);
	return 0;
}