#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define FIFO_FILE3 "/tmp/fifo3"
#define FIFO_FILE4 "/tmp/fifo4"

const float PI = 3.14;
const long MAX_WIDTH = 10000;
const long MAX_HEIGHT= 10000;

struct pixel_array {
    int a[MAX_WIDTH][MAX_HEIGHT];
};


void gaussian_filter(char *photo_address , char *new_photo_address){
	
	//body of function gaussian_filter
}

struct pixel_array calculate_gaussin(int in_pixels[MAX_WIDTH][MAX_HEIGHT], int width, int height){
	
	struct pixel_array pa;
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			pa.a[i][j] = in_pixels[i][j];
		}
	}

	return pa;
}

void calculate_histogram(char *photo_address){
	unsigned char header[54];
	unsigned char pixel;
	unsigned char pixel2;

	FILE *fIn = fopen(photo_address, "rb");
	FILE *fOut = fopen("./output.bmp", "w+b");

	fread(header, sizeof(unsigned char), 54, fIn);

	fwrite(header, sizeof(unsigned char), 54, fOut);

	int width = *(int*)&header[18];
	int height = abs(*(int*)&header[22]);

	int in_pixels[width][height];

	printf("width=%d\nheight=%d\n",width,height);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			fread(&pixel, 1, 1, fIn);
			in_pixels[x][y] = pixel;
                        calculate_gaussin(in_pixels, width, height);
			printf("pixel=%d\n",pixel);
			printf("in_pixel[%d][%d]=%d\n", x, y, in_pixels[x][y]);			


		}
	}
	

	fclose(fIn);
}

int main(){
	printf("start\n");
	//calculate_histogram("./input1.bmp");
	calculate_histogram("./input2.bmp");
}
