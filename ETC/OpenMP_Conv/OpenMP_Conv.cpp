#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 10368
#define HEIGHT 7776

void Conv(int wid, int hei) {

	double val = 0;

	for (int y = 1; y<hei - 1; y++) {
		for (int x = 1; x<wid - 1; x++) {

			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if ((i == -1 && j == -1) || (i == 1 && j == -1))
						val += buff[y + i][x + j] * -1;
					else if ((i == -1 && j == 1) || (i == 1 && j == 1))
						val += buff[y + i][x + j];
					else if (i == 0 && j == -1)
						val += buff[y + i][x + j] * -2;
					else if (i == 0 && j == 1)
						val += buff[y + i][x + j] * 2;
				}
			}

			Res_buff[y][x] = (unsigned char)val;

			val = 0;
		}
	}
}

int main() {

	FILE *fp;
	int Sum[256];
	unsigned char *buf;

	buf = (unsigned char *)malloc(WIDTH *HEIGHT);
	memset(Sum,0,sizeof(Sum));

	fopen_s(&fp, "image.RAW", "rb");
	fread(buf, 1, WIDTH * HEIGHT, fp);
	fclose(fp);

	for (int i = 0; i < HEIGHT; i++) 
		for (int j = 0; j < WIDTH; j++) 
			Sum[buf[i*HEIGHT + j]]++;

	fopen_s(&fp, "conv_image.RAW", "wb");
	fwrite(buf, 1, WIDTH * HEIGHT, fp);
	fclose(fp);
}