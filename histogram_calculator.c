#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE1 "/tmp/fifo1"
#define FIFO_FILE2 "/tmp/fifo2"

void calculate_histogram(char *photo_address ,int *histogram );
int main(){
	
	//Variables
	char photo_address[100];
	int histogram1[256] = {0} ;
	int histogram2[256] = {0} ;
	int fd_1 ,fd_2;
	int read_bytes;
	
	//Open  named pipe betweem process C and B	
	fd_1 = open(FIFO_FILE1 , O_RDONLY);
	fd_2 = open(FIFO_FILE2 , O_WRONLY);
	
	//Get the photo address before applying Gaussiaread_bytes = read(fd_1 , photo_address , sizeof(photo_address));n filter from process C
	read_bytes = read(fd_1 , photo_address , sizeof(photo_address));
	photo_address[read_bytes] = '\0';
	printf("photo address is resived from process C in process A is: %s\n" , photo_address );
	
	
	
	//Calculate the histogram for input photo before applying Gaussian filter
	calculate_histogram(photo_address ,histogram1 );
	
	//Send photo histogram to C process
	write(fd_2 , histogram1 , 256*sizeof(int));

	//Get the new photo address after applying Gaussian filter	from process C
	read_bytes = read(fd_1 , photo_address , sizeof(photo_address));
	photo_address[read_bytes] = '\0';
	

	//Calculate the histogram for input photo after applying Gaussian filter
	calculate_histogram(photo_address ,histogram2 );


	//Send photo histogram to C process
	write(fd_2 , histogram2 , 256*sizeof(int));

	return 0;
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





