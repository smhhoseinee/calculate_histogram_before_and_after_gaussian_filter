#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE1 "/tmp/fifo1"
#define FIFO_FILE2 "/tmp/fifo2"
#define FIFO_FILE3 "/tmp/fifo3"
#define FIFO_FILE4 "/tmp/fifo4"

int main(){

	//Variables
	char *args[] = {"./histogram","./filtering", NULL};
	char new_photo_address [100] ;
	char photo_address [100] ;
	int histogram_1[256];
	int histogram_2[256];
	int fd1[2];
	int fd2[2];
	
	
	//Create two-way pips in order to exchange information between processe main and C 
	pipe(fd1);
	pipe(fd2);


	//Create process A
	if(fork() == 0){
		execvp(args[0] , args);
		exit(0);
	}
	//Create process B
	else if(fork() == 0){
		execvp(args[1] , args);
		exit(0);
	}
	// Create process C
	else if(fork() == 0){

		int histogram1[256] = {0};
		int histogram2[256] = {0};
		char new_address [100] ;
		char address [100] ;
		int fd_1 , fd_2 ,fd_3 ,fd_4 ,read_byte ;
		

		//cominucate with main process to obtain photo address
		close(fd1[1]);
		read(fd1[0] , address , sizeof(address));
		printf("photo address is resived from process main in process C is: %s\n" , address );

		//Create two named pipes in order to cominucate with process A and B
		mknod(FIFO_FILE1, S_IFIFO | 0640, 0);
		mknod(FIFO_FILE2, S_IFIFO | 0640, 0);
		mknod(FIFO_FILE3, S_IFIFO | 0640, 0);
		mknod(FIFO_FILE4, S_IFIFO | 0640, 0);
		
		//Open a named pipe betweem process C and (A,B)	
		fd_1 = open(FIFO_FILE1 , O_WRONLY);
		fd_2 = open(FIFO_FILE2 , O_RDONLY);
		fd_3 = open(FIFO_FILE3 , O_WRONLY);
		fd_4 = open(FIFO_FILE4 , O_RDONLY);
		
		// Send photo address to process A and B
		write(fd_1 , address , strlen(address));
		write(fd_3 , address , strlen(address));

		//Get the entrance photo histogram before applying the Gaussian filter from the process A and 
		//send it to the main process
		sleep(1);
		read(fd_2 , histogram1 , 256*sizeof(int));
		
		close(fd2[0]);
		write(fd2[1] , histogram1 , 256*sizeof(int));
		
		exit(0);
		
	}
	
	//Get photo address from the user
	printf("Please enter the photo address: ");
	fgets(photo_address , sizeof(photo_address) , stdin);
	int stringlen = strlen(photo_address);
	photo_address[stringlen - 1] = '\0'	;
	
	//Send photo address to process C
	close(fd1[0]);
	write(fd1[1] , photo_address ,sizeof(photo_address));
	sleep(1);
	printf("photo address is resived from User in process main is: %s\n" , photo_address );
	
	
	//Get the entrance photo histogram before applying the Gaussian filter from the process C
	close(fd2[1]);
	read(fd2[0] , histogram_1 , 256*sizeof(int));
	printf("The histogram of the input photo is :\n");
	for(int i = 0 ; i < 256 ; i++){
		printf("%-5d ", histogram_1[i]);
		if(i%15 == 0){
			printf("\n");
		}
	}

	
}
