//Authors: Peyton Gardipee and Tushar Verma
//CS537 Fall 2018
//File Purpose:
//Return the userID. A pid is passed in to guarentee that a valid PID is used when navigating
//the proc directory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "readFile.h"

#define LINE_MAX 1000

int readFile(int pidNum) {
	
	FILE *fd;
	char *path = NULL;
	char line[LINE_MAX];
	int lineNumber = 0;
	int myUserID = 0;

	const char *str = "/proc/status/32768";
	int pathLength = strlen(str) ;

	//dynamically allocate memory to path based on path length
	path = malloc(sizeof(char) * pathLength);

	//construct dir path by using the pid
	sprintf(path,"/proc/%d/status",pidNum);

	//open the file
	fd = fopen(path,"r");

	if (fd == NULL) {
		puts("status: File cannot be opened");
		exit(-1);
	}
	else {
		//Parse through the status file to get the UID held in the 8th token
		while(fgets(line,LINE_MAX,fd) != NULL)	{
			if (lineNumber == 8 ) {	
				sscanf(line, "%*s %d", &myUserID);
			}
			lineNumber = lineNumber + 1;	
		}
		fclose(fd);
	}	

	free(path);
	return myUserID;
}	
