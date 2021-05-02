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


void gaussian_filter(char *photo_address , char *new_photo_address){
	
	//body of function gaussian_filter
	
}

void gaussian_array(){

}

void calculate_histogram(char *photo_address){
	unsigned char header[54];
	unsigned char pixel;
	unsigned char pixel2;

	FILE *fIn = fopen(photo_address, "rb");
	FILE *fOut = fopen("./output.bmp", "w+b");

	fread(header, sizeof(unsigned char), 54, fIn);


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
			printf("pixel=%d\n",pixel);
			printf("in_pixel[%d][%d]=%d\n", x, y, in_pixels[x][y]);			


		}
	}
	
	fwrite(header, sizeof(unsigned char), 54, fOut);

	fclose(fIn);
}

int main(){
	printf("start\n");
	//calculate_histogram("./input1.bmp");
	calculate_histogram("./input2.bmp");
}
