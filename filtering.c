#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// Load image using the stb_image library, convert the image to gray and sepia, write it back to disk
#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb_image_write.h"



#define FIFO_FILE3 "/tmp/fifo3"
#define FIFO_FILE4 "/tmp/fifo4"

const float PI = 3.14;

void gaussian_filter(char *photo_address , char *new_photo_address);

int main(){
	
	//Variables	
	char photo_address[100];
	char new_photo_address[100];
	int fd_1 , fd_2;
	int read_bytes;
	
	//Open a named pipe betweem process B and C
	fd_1 = open(FIFO_FILE3 , O_RDONLY);
	fd_2 = open(FIFO_FILE4 , O_WRONLY);
	
	//Get the photo address from process C
	read_bytes = read(fd_1 , photo_address , sizeof(photo_address));
	photo_address[read_bytes] = '\0';
	printf("photo address is resived from process C in process B is: %s\n" , photo_address );

	//Apply Gaussian filter on input photo
	gaussian_filter(photo_address , new_photo_address);
	
	//Send new photo address after applying Gaussian filter to process C.
//	write(fd_2 , new_photo_address , sizeof(new_photo_address));
	write(fd_2 , photo_address , sizeof(photo_address));
	
	//End process B and close named pipe
	close(fd_1);
	close(fd_2);

	return 0;
}

void gaussian_filter(char *photo_address , char *new_photo_address){
	
//	char* postfix = "_gaussin"; 
//	new_photo_address = photo_address;
//	strcat(new_photo_address, postfix);

	new_photo_address = "./output.bmp";

	char* str1;
	char* str2;
	char* str3;
	str1 = "./gauss_blur/blur";
	str2 = photo_address;
	str3 = "temp.png";
	char * str4 = (char *) malloc(1 + sizeof(char*) * (strlen(str1) + strlen(str2) + strlen(str3)));
	strcpy(str4, str1);
	strcat(str4, " ");
	strcat(str4, str2);
	strcat(str4, " ");
	strcat(str4, str3);


	printf("\ncommand to execute: %s\n",str4);

	// Create temp.png blured image with gaussin filter
	system(str4);

	int width, height, channels;
	unsigned char *img = stbi_load(str3 , &width, &height, &channels, 0);
	if(img == NULL) {
		printf("loading %s failed :  maybe file is not available in the path or permission is denied\n",str3);
		exit(1);
	}
	printf("%s[%d][%d]px successfully loaded ,channels=%d\n",str3, width, height, channels);

	stbi_write_bmp(new_photo_address, width, height, channels, img);

	stbi_image_free(img);

}

void calculate_histogram(char *photo_address ,int *histogram ){
	unsigned char header[54];
	unsigned char pixel;

	FILE *fIn = fopen(photo_address, "rb");
	fread(header, sizeof(unsigned char), 54, fIn);

	int width = *(int*)&header[18];
	int height = abs(*(int*)&header[22]);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			fread(&pixel, 1, 1, fIn);
			histogram[pixel]++;
		}
	}
	fclose(fIn);
}


