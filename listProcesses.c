//Authors: Peyton Gardipee and Tushar Verma
//CS537 Fall 2018
//File Purpose:
//Find all PIDS that exist in the proc folder. Return an array of PIDS that belong to the user and set the arraySize variable
//that is passed in as a parameter.

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "readFile.h"

#define BUFFSIZE 1024 
#define DNAMESIZE 256	//Given in manual page
#define BASETEN 10


int* listprocess(int* arraySize) {
	DIR *dir,*dir1;
	struct dirent *entry;
	char *dirName = malloc(sizeof(char) * BUFFSIZE);
	char *statusDir = malloc(sizeof(char) * BUFFSIZE);
	FILE *fd = NULL;
	int myuserID =0;
	int userID = geteuid();
	char *end = NULL;
	int numOfPids =0;
	char userPIDs[BUFFSIZE][DNAMESIZE];
	static int userPIDNums[BUFFSIZE];

	//Open proc directory
	if ((dir = opendir("/proc")) == NULL) {
		perror("opendir() error");
	}

	else {
		//Iterate through each folder in proc 
		while ((entry = readdir(dir)) != NULL) {
			//Assume all folders with digits for name are folders for PIDs
			if(isdigit(entry->d_name[0]) !=0 ) {
				//Builds process ID dir 
				strcpy(dirName,"/proc/");
				strcat(dirName,entry->d_name);

				if (( dir1 = opendir(dirName)) == NULL) { 
					perror(" no pid dir found");
					puts(" no pid dir found");
				}

				//Builds status dir inside each process ID
				strcpy(statusDir,dirName);
				strcat(statusDir,"/status");

				fd = fopen(statusDir,"r");

				if(fd == NULL) {
					puts("fd is null");
					exit(EXIT_FAILURE);
				}
				else {
					//enters into status file successfully	
					myuserID = readFile(strtol(entry->d_name, &end, BASETEN));
					if (userID == myuserID) {
						//Get only PIDS that belong to the current user
						strcat(userPIDs[numOfPids],entry->d_name);
						numOfPids = numOfPids + 1;
					}
				}
	    	}	
		} //end of while loop

		//Assign array size for use in main
		*arraySize = numOfPids;

		//Assign all pids to passed in array for use in main
		for (int i =0; i<numOfPids;i++) {
			userPIDNums[i] = strtol(userPIDs[i], &end, BASETEN);
		}
		fclose(fd);
		closedir(dir);
	}
	//fclose(fd);	
	//closedir(dir);
	free(statusDir);
	free(dirName);

	return userPIDNums;
}



