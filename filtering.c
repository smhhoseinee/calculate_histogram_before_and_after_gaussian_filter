#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE3 "/tmp/fifo3"
#define FIFO_FILE4 "/tmp/fifo4"

int main(){
	
	//Variables	
	char photo_address[100];
	char new_photo_address[100];
	int fd_1 , fd_2;
	int read_bytes;
	
	//Open a named pipe betweem process C and B	
	fd_1 = open(FIFO_FILE3 , O_RDONLY);
	fd_2 = open(FIFO_FILE4 , O_WRONLY);
	
	//Get the photo address from process C
	read_bytes = read(fd_1 , photo_address , sizeof(photo_address));
	photo_address[read_bytes] = '\0';
	printf("photo address is resived from process C in process A is: %s\n" , photo_address );

	return 0;
}


