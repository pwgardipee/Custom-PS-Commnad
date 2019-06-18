//Authors: Peyton Gardipee and Tushar Verma
//CS537 Fall 2018
//File Purpose:
//Given a PID from the user, determine if that PID exists. Return true if it does exist, flase otherwise.

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "readFile.h"

#define BASETEN 10
#define BUFFSIZE 1024


int isPidValid(int pidNum) {

	DIR *dir;
	struct dirent *enterProc;
	char *dirName = malloc(sizeof(char) *BUFFSIZE);
	char *end = NULL; //Used for strtol
	int pidValid = 0; //bool variable 

	//Open proc folder 
	if ((dir = opendir("/proc")) == NULL) {
		perror("opendir() error");
	}
	else {
		//Iterate through each folder name
		while ((enterProc = readdir(dir)) != NULL) {

			//isDigit() returns a non zero value if entry->d_name starts with a digit
			if(isdigit(enterProc->d_name[0]) !=0 ) {
			
				//Builds process ID dir 
				strcpy(dirName,"/proc/");
				strcat(dirName,enterProc->d_name);

				if (pidNum == strtol(enterProc->d_name,&end,BASETEN)) {
					//The pid from the user exists in the proc folder
					pidValid = 1;
				}
	    	}	
		} 
		closedir(dir);
	}	
	
	free(dirName);

	return pidValid;
}



