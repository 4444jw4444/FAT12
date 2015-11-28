#include <stdint.h>
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
#define subMask 0x10
#define labelMask 0x08
void print_file(){
	printf("Trying to print out a file's information\n");
}
void print_directory(){
	printf("Trying to print out a directory's information\n");
}

int main(int argc, char* argv[]){
        //check that the user has input the right number of commands 
    if(argc != 2){
        printf("Please enter a command in the format ./diskinfo <disk image file name>\n");
        return -1;
    }
    //try to open the disk image
    FILE* fo;
    fo = fopen(argv[1],"rb");
    //check that the file open didn't fail
    if(fo == NULL){
        printf("ERROR:File: %s unavailable or corrupt, please specifiy a valid file\n", argv[1]);
        return -1;
    }
    printf("Attempting list disk information: %s\n", argv[1]);
    //fseek(fo,offset,whence)
    //fread(pointer,size,number,stream)
    int readByte = 0;
    int i = 0;
    int offset = 32;
    char fileName[9];
    char extName[4];
    char creationTime[3];
    char creationDate[3];
    const char space[2] = " ";
    char fileSize[5];
    int iFileSize = 0;
    while(1){
	fseek(fo,(512*19) + (offset*i),SEEK_SET);
	fread(&readByte,1,1,fo);
	if(readByte == 0){
		break;
	}
	if(readByte == 0xe5){
		continue;
	}
	fseek(fo,10,SEEK_CUR);
	fread(&readByte,1,1,fo);
	int lAndr = labelMask & readByte;
	int sAndr = subMask & readByte;
	//printf("lAndr: %d , sAndr: %d\n", lAndr, sAndr);
	if(lAndr == 0){
		fseek(fo,(512*19) +(offset*i),SEEK_SET);
		fread(&fileName,8,1,fo);
		fileName[8] = '\0';
		strtok(fileName,space);
		fread(&extName,3,1,fo);
		extName[3] = '\0';
		strtok(extName,space);
		fseek(fo,(512*19) + 14,SEEK_SET);
		fread(&creationTime,2,1,fo);
		creationTime[2] = '\0';
		fread(&creationDate,2,1,fo);
		creationDate[2] = '\0';
		fseek(fo,(512*19) + 28,SEEK_SET);
		fread(&fileSize,4,1,fo);
		fileSize[4] = '\0';
		printf("fileSize: %s\n", fileSize);
		iFileSize = atoi(fileSize);
		printf("F %d %s.%s %s.%s\n",iFileSize,fileName,extName,creationTime,creationDate);
	}
	/*if(sAndr == 0){
		print_directory();
	}*/

	i++;
    }
    printf("Exiting\n");
}
