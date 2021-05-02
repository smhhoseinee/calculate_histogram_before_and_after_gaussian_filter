#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<unistd.h>

int main(){

	//Variables
	char *args[] = {"./histogram","./filtering", NULL};
	char photo_address [100] ;
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

		char address [100] ;

		//cominucate with main process to obtain photo address
		close(fd1[1]);
		read(fd1[0] , address , sizeof(address));
		printf("Address is resived from main is: %s\n" , address);
		
		exit(0);
		
	}
	
	sleep(1);
	//Get photo address from the user
	printf("Please enter the photo address: ");
	fgets(photo_address , sizeof(photo_address) , stdin);
	int stringlen = strlen(photo_address);
	photo_address[stringlen - 1] = '\0'	;
	
	//Send photo address to process C
	close(fd1[0]);
	write(fd1[1] , photo_address ,sizeof(photo_address));
	
	printf("Address is: %s\n" , photo_address);
	
}
