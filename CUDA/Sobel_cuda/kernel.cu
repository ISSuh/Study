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
#include <string.h>

static void HandleError(cudaError_t err, const char *file, int line) {
	if (err != cudaSuccess) {
		printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
		exit(EXIT_FAILURE);
	}
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

#define WIDTH		256
#define HEIGHT		256
#define MR			3
#define MC			3
#define	MASK_N		3

const int N = 1024;
const int threadsPerBlock = 1024;
const int blocksperGrid = 5;

int MaskSobelX[3][3] = { { -1,0,1 },
{ -2,0,2 },
{ -1,0,1 } };

int MaskSobelY[3][3] = { { 1,2,1 },
{ 0,0,0 },
{ -1,-2,-1 } };
	
__global__ void Sobel_Conv(unsigned char *d_InImg, int *d_ConvX, int *d_ConvY, int width, int height, int mr, int mc, int size) {
	int outputX = 0, outputY = 0;
	int col = threadIdx.x + blockIdx.x * blockDim.x;
	int row = threadIdx.y + blockIdx.y * blockDim.y;
	int i, j;

	int MaskSobelX[3][3] = { { -1,0,1 },
	{ -2,0,2 },
	{ -1,0,1 } };

	int MaskSobelY[3][3] = { { 1,2,1 },
	{ 0,0,0 },
	{ -1,-2,-1 } };

	if ((0 < row && row < height -1) && (0 < col && col < width-1)) {
		for (i = 0; i < mr; i++) {
			for (j = 0; j < mc; j++) {
				outputX += MaskSobelX[i][j] * d_InImg[(row + i - 1) * width + (col + j - 1)];
				outputY += MaskSobelY[i][j] * d_InImg[(row + i - 1) * width + (col + j - 1)];
			}
		}

		d_ConvX[row*width + col] = outputX;
		d_ConvY[row*width + col] = outputY;
	}

	else {
		d_ConvX[row*width + col] = 0;
		d_ConvY[row*width + col] = 0;
	}
}


__global__ void Detect_Edge(unsigned char *d_OrgImg, int *d_ConvX, int *d_ConvY,int *d_pImgSobel ,int width, int height,int *d_min,int *d_max) {

	int col = threadIdx.x + blockIdx.x * blockDim.x;
	int row = threadIdx.y + blockIdx.y * blockDim.y;
	int temp1, temp2;
	
	if ((row != 1 && row != height - 1) && (col != 1 && col != width - 1)) {
		if (d_ConvX[row*width + col] < 0)
			d_ConvX[row*width + col] = -d_ConvX[row*width + col];
		if (d_ConvY[row*width + col] < 0)
			d_ConvY[row*width + col] = -d_ConvY[row*width + col];

		d_pImgSobel[row*width + col] = d_ConvX[row*width + col] + d_ConvY[row*width + col];

		if (d_pImgSobel[row*width + col] < *d_min)
			*d_min = d_pImgSobel[row*width + col];
		if (d_pImgSobel[row*width + col] > *d_max)
			*d_max = d_pImgSobel[row*width + col];
	}

	__syncthreads();
						
	
	temp1 = (float)(255.0 / (*d_max - *d_min));
	temp2 = (float)(-255.0**d_min / (*d_max - *d_min));

	if ((row != 1 && row != height - 1) && (col != 1 && col != width - 1))
			d_OrgImg[row*width + col] = (unsigned char)(temp1*d_pImgSobel[row*width + col] + temp2);

}

int main()
{
	int min, max;
	int *dev_min, *dev_max;
	int *ConvX, *ConvY, *pImgSobel;
	int *dev_ConvX, *dev_ConvY,*dev_pImgSobel;
	float temp1, temp2;
	unsigned char *InImg;
	unsigned char *dev_InImg;
	unsigned char *OrgImg;
	unsigned char *dev_OrgImg;
	int newValue, Xval, Yval;
	int mr, mc;

	clock_t PL_start, PL_end;

	min = (int)10e10;
	max = (int)-10e10;

	InImg = (unsigned char*)malloc(sizeof(unsigned char)*(HEIGHT*WIDTH));
	OrgImg = (unsigned char*)malloc(sizeof(unsigned char)*(HEIGHT*WIDTH));

	FILE *infile = fopen("256x256.raw", "rb");
	fread(InImg, sizeof(unsigned char), HEIGHT * WIDTH, infile);
	fclose(infile);

	pImgSobel = (int*)malloc(sizeof(int)*(HEIGHT*WIDTH));
	ConvX = (int*)malloc(sizeof(int)*(HEIGHT*WIDTH));
	ConvY = (int*)malloc(sizeof(int)*(HEIGHT*WIDTH));

	memset(ConvX, 0, (HEIGHT*WIDTH) * sizeof(int));
	memset(ConvY, 0, (HEIGHT*WIDTH) * sizeof(int));
	memset(OrgImg, 0, (HEIGHT*WIDTH) * sizeof(unsigned char));
	memset(pImgSobel, 0, (HEIGHT*WIDTH) * sizeof(int));
	
	PL_start = clock();

	HANDLE_ERROR(cudaMalloc((void**)&dev_InImg, WIDTH * HEIGHT * sizeof(unsigned char)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_ConvX, WIDTH * HEIGHT * sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_ConvY, WIDTH * HEIGHT * sizeof(int)));

	HANDLE_ERROR(cudaMemcpy(dev_InImg, InImg, WIDTH * HEIGHT * sizeof(unsigned char), cudaMemcpyHostToDevice));
	
	Sobel_Conv << <blocksperGrid, threadsPerBlock >> > (dev_InImg, dev_ConvX, dev_ConvY, WIDTH, HEIGHT, MR, MC, WIDTH * HEIGHT);  
	HANDLE_ERROR(cudaDeviceSynchronize());

	HANDLE_ERROR(cudaMemcpy(ConvX, dev_ConvX, WIDTH * HEIGHT * sizeof(int), cudaMemcpyDeviceToHost));
	HANDLE_ERROR(cudaMemcpy(ConvY, dev_ConvY, WIDTH * HEIGHT * sizeof(int), cudaMemcpyDeviceToHost));

	for (int i = 1000; i < HEIGHT; i++)
		for (int j = 1000; j < WIDTH; j++)
			printf("[%d][%d] %d %d\n",i,j,ConvX[i*WIDTH + j],ConvY[i*WIDTH + j]);

	/*for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {
			Xval = 0;
			Yval = 0;

			for (mr = 0; mr < MASK_N; mr++) {
				for (mc = 0; mc < MASK_N; mc++) {
					Xval += (MaskSobelX[mr][mc] * InImg[(i + mr - 1) * WIDTH + (j + mc - 1)]);
					Yval += (MaskSobelY[mr][mc] * InImg[(i + mr - 1) * WIDTH + (j + mc - 1)]);
				}
			}

			ConvX[i*WIDTH + j] = Xval;
			ConvY[i*WIDTH + j] = Yval;
		}
	}*/

	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {

			temp1 = ConvX[i*WIDTH + j];
			temp2 = ConvY[i*WIDTH + j];

			if (temp1 < 0)
				temp1 = -temp1;
			if (temp2 < 0)
				temp2 = -temp2;

			pImgSobel[i*WIDTH + j] = temp1 + temp2;
		}
	}

	//최대값,최소값 탐색
	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {

			if (pImgSobel[i*WIDTH + j]<min)
				min = pImgSobel[i*WIDTH + j];
			if (pImgSobel[i*WIDTH + j]>max)
				max = pImgSobel[i*WIDTH + j];

		}
	}

	//변환시 상수값을 미리 계산 
	temp1 = (float)(255.0 / (max - min));
	temp2 = (float)(-255.0*min / (max - min));

	for (int i = 1; i<HEIGHT - 1; i++) {
		for (int j = 1; j<WIDTH - 1; j++) {
			//[min,max]사이의 값을 [0,255]값으로 변환 
			newValue = pImgSobel[i*WIDTH + j];
			newValue = temp1 * newValue + temp2;
			OrgImg[i*WIDTH + j] = (unsigned char)newValue;
		}
	}

	
	/*HANDLE_ERROR(cudaMalloc((void**)&dev_OrgImg, WIDTH * HEIGHT * sizeof(unsigned char)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_ConvX, WIDTH * HEIGHT * sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_ConvY, WIDTH * HEIGHT * sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_pImgSobel, WIDTH * HEIGHT * sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_min, HEIGHT * sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_max, HEIGHT * sizeof(int)));

	HANDLE_ERROR(cudaMemset(dev_min,0,sizeof(int)));
	HANDLE_ERROR(cudaMemset(dev_max, 0, sizeof(int)));

	HANDLE_ERROR(cudaMemcpy(dev_ConvX, ConvX, WIDTH * HEIGHT * sizeof(int), cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_ConvY, ConvY, WIDTH * HEIGHT * sizeof(int), cudaMemcpyHostToDevice));

	Detect_Edge << <HEIGHT, WIDTH>> > (dev_OrgImg, dev_ConvX, dev_ConvY, dev_pImgSobel, WIDTH, HEIGHT,dev_min,dev_max);

	HANDLE_ERROR(cudaMemcpy(OrgImg, dev_OrgImg, WIDTH * HEIGHT * sizeof(unsigned char), cudaMemcpyDeviceToHost));*/

	PL_end = clock();

	FILE *outfile = fopen("CS.raw", "wb");
	fwrite(OrgImg, sizeof(unsigned char), HEIGHT * WIDTH, outfile);
	fclose(outfile);

	printf("Finish\n");
	printf("Block per Grid			:  %d\n",blocksperGrid);
	printf("Thread per Block		:  %d\n",threadsPerBlock);
	printf("Average Parallel Runtime 	: %f\n", (float)(PL_end - PL_start) / CLOCKS_PER_SEC);

	cudaFree(dev_ConvX);
	cudaFree(dev_ConvY);
	//cudaFree(dev_OrgImg);
	//cudaFree(dev_pImgSobel);
	//cudaFree(dev_min);
	//cudaFree(dev_max);

	free(InImg);
	free(OrgImg);
	free(pImgSobel);
	free(ConvX);
	free(ConvY);
}