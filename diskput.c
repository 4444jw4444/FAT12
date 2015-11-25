#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <signal.h>
typedef int bool;
#define true 1
#define false 0

int main(int argc, char* argv[]){ 
    //check that the user has input the right number of commands 
    if(argc != 2){
    	printf("Please enter a command in the format ./diskget <disk image file name>\n");
    	return -1;
    }
    printf("Attempting to put information on disk: %s\n", argv[1]);
    //create all the processes
    //we are in a child
    printf("Exiting\n");
}