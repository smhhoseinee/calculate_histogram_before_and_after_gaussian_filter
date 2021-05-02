#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE1 "/tmp/fifo1"
#define FIFO_FILE2 "/tmp/fifo2"

int main(){
	
	//Variables
	char photo_address[100];
	int histogram[256] = {0} ;
	int fd_1 ,fd_2;
	int read_bytes;
	
	//Open  named pipe betweem process C and B	
	fd_1 = open(FIFO_FILE1 , O_RDONLY);
	fd_2 = open(FIFO_FILE2 , O_WRONLY);
	
	//Get the photo address before applying Gaussian filter
	read_bytes = read(fd_1 , photo_address , sizeof(photo_address));
	photo_address[read_bytes] = '\0';
	printf("photo address is resived from process C in process B is: %s\n" , photo_address );

	return 0;
}



