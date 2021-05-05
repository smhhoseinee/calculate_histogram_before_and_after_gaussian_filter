#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define FIFO_FILE3 "/tmp/fifo3"
#define FIFO_FILE4 "/tmp/fifo4"

#define MAX_WIDTH  10000
#define MAX_HEIGHT 10000

const float PI = 3.14;

int in_pixels[MAX_WIDTH][MAX_HEIGHT];

struct pixel_array {
//    int values[MAX_WIDTH][MAX_HEIGHT];
    int** values;
};


void gaussian_filter(char *photo_address , char *new_photo_address){
	
	//body of function gaussian_filter
}

struct pixel_array calculate_gaussin(int in_pixels[MAX_WIDTH][MAX_HEIGHT], int width, int height){
	
	struct pixel_array pa;
	pa.values = malloc(width*sizeof(int*)); // allocates one dimension
	for(int i = 0; i < width; i++) {
	        pa.values[i] = malloc(height*sizeof(int)); // allocates second one dimension
	}

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			printf("i=%d j=%d\n",i,j);
			pa.values[i][j] = in_pixels[i][j];

		}
	}

	return pa;
}

int **calculate_gaussin2(int in_pixels[MAX_WIDTH][MAX_HEIGHT], int width, int height){
	int **values;
	values = (int **)malloc(width*sizeof(int*)); // allocates one dimension
	for(int i = 0; i < width; i++) {
	        values[i] = (int *)malloc(height*sizeof(int)); // allocates second one dimension
	}

	int x;
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			//printf("i=%d j=%d\n",i,j);
			//values[i][j] = in_pixels[i][j];
			printf("in_pixel[%d][%d]=%d\n", i, j, in_pixels[i][j]);			
			x  = in_pixels[i][j];
			printf("x=%d\n\n",x);
			values[i][j] = x;

		}
	}

	return values;
}

int calculate_gaussin3(int width, int height){
	int temp_pixels[MAX_WIDTH][MAX_HEIGHT];
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			//printf("i=%d j=%d\n",i,j);
			//values[i][j] = in_pixels[i][j];
			printf("in_pixel[%d][%d]=%d\n", i, j, in_pixels[i][j]);			
			temp_pixels[i][j] = in_pixels[i][j];
		}
	}




	return 0;
}




void calculate_histogram(char *photo_address){
	printf("2nd\n");
	unsigned char header[54];
	unsigned char pixel;
	unsigned char pixel2;

	FILE *fIn = fopen(photo_address, "rb");

	FILE *fOut = fopen("./output.bmp", "w+b");

	fread(header, sizeof(unsigned char), 54, fIn);
	fwrite(header, sizeof(unsigned char), 54, fOut);

	int width = *(int*)&header[18];
	int height = abs(*(int*)&header[22]);

	int out_pixels[width][height];

	printf("width=%d\nheight=%d\n",width,height);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			fread(&pixel, 1, 1, fIn);
			in_pixels[x][y] = pixel;
			//printf("pixel=%d\n",pixel);
			//printf("in_pixel[%d][%d]=%d\n", x, y, in_pixels[x][y]);			
		}
	}

	//struct pixel_array out_pixel_array = calculate_gaussin(in_pixels, width, height);
	//int **out_pixel_array = calculate_gaussin2(in_pixels, width, height);
	calculate_gaussin3(width, height);

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{

			//			unsigned char charInt =  (unsigned char)out_pixel_array.a[x][y] ;
			//			memset(&pixel, charInt, sizeof(pixel));
//			printf("pixel=%d\n",pixel);
//			printf("in_pixel[%d][%d]=%d\n", x, y, out_pixels[x][y]);			
//			printf("in_pixel[%d][%d]=%d\n", x, y, in_pixels[x][y]);			
			fwrite(&pixel, 1, 1, fOut);
		}
	}
	

	fclose(fIn);
	fclose(fOut);
}

int main(){
	printf("start\n");
	//calculate_histogram("./input1.bmp");
	//calculate_histogram("./input2.bmp");

	char* str1;
	char* str2;
	char* str3;
	str1 = "./gauss_blur/blur";
	str2 = "./sky.jpg";
	str3 = "./sky.png";
	char * str4 = (char *) malloc(1 + sizeof(char*) * (strlen(str1) + strlen(str2) + strlen(str3)));
	strcpy(str4, str1);
	strcat(str4, " ");
	strcat(str4, str2);
	strcat(str4, " ");
	strcat(str4, str3);

	printf("\n%s\n",str4);

	//char *x = "./gauss_blur/blur "
	//system("./gauss_blur/blur ./sky.jpg ./sky.png");
	system(str4);
	
}
