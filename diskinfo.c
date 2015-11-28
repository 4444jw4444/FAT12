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
    ///---Display OS
    //seek to the operating system information
    fseek(fo, 3, SEEK_SET);
    //alloc an object to hold the recieved input from the disk image
    char OSLine[9];
    //read in a chunk of data
    fread(OSLine,8,1,fo);
    //add the string terminator
    OSLine[8] = '\0';
    //display the Operating system
    
    ///---Display FileLabel
    //seek to the label
    fseek(fo,43, SEEK_SET);
    //create label holder
    char fileLabel[11];
    //read in a chunk of data
    fread(fileLabel,11,1,fo);
    //add the string terminator
    fileLabel[10] = '\0';
    //display the Disk Label
    
    ///---Calculate total space
    //print the value that is the same for all fat12 floppy disks
    
    
    ///---Determine the free space
    //Access the FAT table and read each entry there
    //fseek(fo,512,SEEK_SET);
    //int i;
    //unsigned int twoFat[13];
    //twoFat[0] = 0x0;
    //read in two entries simultaneously for each loop
    //fread(twoFat, 12, 1, fo);
    //printf("Here are the first 12 bytes %x %x %x %x %x\n", twoFat[0], twoFat[1], twoFat[2], twoFat[3], twoFat[4]);
    //check if entry one or two is a filled value
    //if they are, then increment the counter
    //if they aren't, then move on
    //calculate the total space that has been used up by subtracting (#fat entries valid * size of memory segments pointed to by fat) 
    //from the total amount of space given by (2879 sectors * 512 bytes)

    ///---Determine the number of files in the root directory
   // uint32_t labelMask = 0x08;
   // uint32_t subMask = 0x10;
    int rootOffset = 32;
    int i = 0;
    uint32_t readByte = 0;
    int count = 0;
    while(1){
	fseek(fo,(512*19)+(rootOffset * i), SEEK_SET);
	fread(&readByte,1,1,fo);
	if(readByte == 0){
		 break;
	}
        if(readByte == 0xe5){
	 continue;
	}
	fseek(fo,10,SEEK_CUR);
	fread(&readByte,1,1,fo);
	//printf("aslkjdlf %d: \n", readByte);
	int lAndr = labelMask & readByte;
	int sAndr = subMask & readByte;
	if((lAndr == 0x0) && (sAndr == 0x0)){
	 count ++;
	}
	//printf("labelMask and readByte: %x, subMask and readByte: %x", (labelMask & readByte), (subMask & readByte));
	i++;
    }
    
    //get the number of FAT tables
    int numOfFAT = 0;
    fseek(fo,16,SEEK_SET);
    fread(&numOfFAT,1,1,fo);

    //get the sectors per FAT table
    int secPerFAT = 0;
    fseek(fo,22,SEEK_SET);
    fread(&secPerFAT,2,1,fo);

    //fseek to the first location of the root directory
    //19 * 512 gives us the first entry in the root directory
    /*fseek(fo,19*512,SEEK_SET);
    //each file in the root directory is a 32 byte chunk. The 11th byte in the 32 byte chunk is the attributes section.
    //we will iterate through all the files that exist and add that together.
    //fseek(fo,11,SEEK_CUR);
    //create a variable to hold the byte that we have read in
    char attribute[1];
    //attribute is one byte, and one of the values found in the table.
    fread(attribute,1,1,fo);
    //check the first byte of each entry to see if its 0xe5. This indicates an empty entry
    if(attribute[0] == 0xe5 || attribute[0] == 0x00)
    
    //if the value is not null (0x00) and not our 0xe5 flag, then the entry is valid. 
    else{
    printf("file exists\n");
    fseek(fo,19*512 + 11,SEEK_SET);
    fread(attribute,1,1,fo);
    printf("attribute %x \n", attribute[0]);
    //bitwise and with the label
    }*/
    
    /*
    //create spaceholder
    int spaceHolder = 0;
    //go through all bytes in the disk and check if they are set to 0, if so, then count them
    int i;
    char oneChar[1];
    for(i = 0; i < 1474048; i ++){
      fseek(fo, i, SEEK_SET);
      fread(oneChar, 1, 1, fo);
      if(oneChar[0] == '0')
      spaceHolder ++;
    }
    //print out the free space on the disk
    printf("Free size of the disk: %d bytes\n", spaceHolder);
    */
    //print the value of possible entries that is the same for all fat12 floppy disks
    //printf("
    printf("OS Name: %s\n", OSLine);
    printf("Label of the disk: %s\n", fileLabel);
    printf("Total size of the disk: %d bytes\n", 2879*512);
    printf("The number of files in the root directory (not including subdirectories): %d\n", count);
    printf("Number of FAT copies: %d\n", numOfFAT);
    printf("Sectors per FAT table: %d\n", secPerFAT); 
    //close the file stream
    fclose(fo);
    //exit successfully
    printf("Success:Exiting\n");
    return 0;
}
//fread
//fseek
//fopen, read-binary
 
