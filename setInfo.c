//Authors: Peyton Gardipee and Tushar Verma
//CS537 Fall 2018
//File Purpose:
//Given the PID passed as a parameter, navigate to the stat and statm folder to get the required infomation.
//Store this information in the fields of the passed info struct

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setInfo.h"

#define LINE_MAX 2024
#define FILENAMESIZE 40

int setInfo(int pid, info* infoHolder){
	
	char fileName[FILENAMESIZE];
	sprintf(fileName,"/proc/%d/stat",pid);

	FILE *fptr;
	char *line = malloc(sizeof(char) * LINE_MAX);
	char* t;

	//Start at 1 to match with manual documentation for proc/<pid>/stat
	int num = 1;
	
	fptr = fopen(fileName, "r");

	if(fptr == NULL){
		perror("error opening file");
	}
	else{
		//Used as buffer
		//line = malloc(sizeof(char) * LINE_MAX);

		while(fgets(line,LINE_MAX,fptr)){

			//Occasionally the contents of the stat file will have two words representing one item.
			//The space between the words can cause the parser to get the wrong item. This logic allows
			//us to take the item which is one char long(assumed to be the correct state code)
			sscanf(line,"%*s %*s %s",infoHolder->state);

			if((strlen(infoHolder->state)) > 1){
					sscanf(line,"%*s %*s %*s %s",infoHolder->state);
			}

			//Get the User time (item 14) and system time (item 15) of stat file
			t = strtok(line," ");
			while(t != NULL){
				if(num == 14){
					infoHolder->uTime = t;
				}
				if(num == 15){
					infoHolder->sTime = t;
				}
				t = strtok(NULL, " ");
				num++;
			}  
		}
	}

	fclose(fptr);

	//Change path to statm file
	sprintf(fileName,"/proc/%d/statm",pid);

    fptr = fopen(fileName, "r");

	if(fptr == NULL){

		printf("COULD NOT OPEN");
	}

	//Use as buffer
	char* line2;
	line2 = (char*)malloc(LINE_MAX*sizeof(char));

    if(fptr == NULL){
        perror("error opening file");
    }
    else{
		//The virtual memory item of this file is the first item
	    fgets(line2, sizeof(line2),fptr);
	    infoHolder->vMem = strtok(line2," ");
    }

    fclose(fptr);
    free(line);
    free(line2);
	return 0;

}
