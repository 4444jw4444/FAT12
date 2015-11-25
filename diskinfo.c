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
    	printf("Please enter a command in the format ./diskinfo <disk image file name>\n");
    	return -1;
    }
    printf("Attempting to gather information on disk: %s\n", argv[1]);
    //try to open the disk image
    FILE* fo;
    fo = fopen(argv[1],"rb");
    //check that the file open didn't fail
    if(fo == NULL){
    	printf("ERROR:File: %s unavailable or corrupt, please specifiy a valid file\n", argv[1]);
    	return -1;
    }
    //close the file stream
    fclose(fo);
    //exit successfully
    printf("Success:Exiting\n");
}
//fread
//fseek
//fopen, read-binary
