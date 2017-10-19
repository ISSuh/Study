#include <math.h>
#include <windows.h>
#include <stdio.h>
using namespace std;

int main()
{

	int height = 256;
	int width = 256;
	int i, j, vmax, vmin;
	int m_HistoArr[256];
	unsigned char InImg[256][256];
	unsigned char OrgImg[256][256];

	FILE *infile = fopen("TEST.raw", "rb");
	if (infile == NULL) { printf("error!"); return 0; }
	fread(InImg, sizeof(char), 256 * 256, infile);
	fclose(infile);


	int MaskSobelX[3][3] = { { -1,0,1 },
	{ -2,0,2 },
	{ -1,0,1 } };
	int MaskSobelY[3][3] = { { 1,2,1 },
	{ 0,0,0 },
	{ -1,-2,-1 } };
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int mr, mc;
	int newValue;

	int *pImgSobelX, *pImgSobelY;
	int min, max, where;
	float constVal1, constVal2;
	//�������� ���� �̹��� ���� �޸� �Ҵ�
	pImgSobelX = new int[height*width];
	pImgSobelY = new int[height*width];
	//��� �̹��� 0���� �ʱ�ȭ
	for (i = 0; i<height; i++)
		for (j = 0; j<width; j++)
		{
			OrgImg[i][j] = 0;
			where = i*width + j;
			pImgSobelX[where] = 0;
			pImgSobelY[where] = 0;
		}
	//X ���� ���� ���� ��� 
	for (i = 1; i<heightm1; i++)
	{
		for (j = 1; j<widthm1; j++)
		{
			newValue = 0; //0���� �ʱ�ȭ
			for (mr = 0; mr<3; mr++)
				for (mc = 0; mc<3; mc++)
					newValue += (MaskSobelX[mr][mc] * InImg[i + mr - 1][j + mc - 1]);
			pImgSobelX[i*width + j] = newValue;
		}
	}

	//Y ���� ���� ���� ��� 
	for (i = 1; i<heightm1; i++)
	{
		for (j = 1; j<widthm1; j++)
		{
			newValue = 0; //0���� �ʱ�ȭ
			for (mr = 0; mr<3; mr++)
				for (mc = 0; mc<3; mc++)
					newValue += (MaskSobelY[mr][mc] * InImg[i + mr - 1][j + mc - 1]);
			pImgSobelY[i*width + j] = newValue;
		}
	}

	//���� ���� ��� ���밪(X)+���밪(Y)�� pImgSobelX[]�� ����
	for (i = 1; i<heightm1; i++)
		for (j = 1; j<widthm1; j++)
		{
			where = i*width + j;
			constVal1 = pImgSobelX[where];
			constVal2 = pImgSobelY[where];
			if (constVal1<0)
				constVal1 = -constVal1;
			if (constVal2<0)
				constVal2 = -constVal2;
			pImgSobelX[where] = constVal1 + constVal2;
		}

	//���÷��̸� ���� 0���� 255���̷� ���� ������ ����
	//�̸� ���� ���� �ִ�,�ּҰ��� ã���� �̸� �̿��Ͽ� �����Ѵ�.
	min = (int)10e10;
	max = (int)-10e10;
	for (i = 1; i<heightm1; i++)
	{
		for (j = 1; j<widthm1; j++)
		{
			newValue = pImgSobelX[i*width + j];
			if (newValue<min)
				min = newValue;
			if (newValue>max)
				max = newValue;
		}
	}
	//��ȯ�� ������� �̸� ��� 
	constVal1 = (float)(255.0 / (max - min));
	constVal2 = (float)(-255.0*min / (max - min));
	for (i = 1; i<heightm1; i++)
	{
		for (j = 1; j<widthm1; j++)
		{
			//[min,max]������ ���� [0,255]������ ��ȯ 
			newValue = pImgSobelX[i*width + j];
			newValue = constVal1*newValue + constVal2;
			OrgImg[i][j] = (BYTE)newValue;
		}
	}
	//���� �Ҵ� �޸� ����
	delete[] pImgSobelX;
	delete[] pImgSobelY;

	FILE *outfile = fopen("result.raw", "wb");
	fwrite(OrgImg, sizeof(char), 256 * 256, outfile);
	fclose(outfile);

	return 0;
}