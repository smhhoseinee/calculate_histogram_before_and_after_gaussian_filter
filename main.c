#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<unistd.h>

int main(){

	//Variables
	char photo_address [100] ;


	//Create process A
	if(fork() == 0){

		exit(0);
	}
	//Create process B
	else if(fork() == 0){
		
		exit(0);
	}
	// Create process C
	else if(fork() == 0){

		exit(0);
		
	}
	
	//Get photo address from the user
	printf("Please enter the photo address: ");
	fgets(photo_address , sizeof(photo_address) , stdin);
	int stringlen = strlen(photo_address);
	photo_address[stringlen - 1] = '\0'	;
	
	
	printf("Address is: %s\n" , photo_address);
	
}