//Authors: Peyton Gardipee and Tushar Verma
//CS537 Fall 2018
//File Purpose:
//Enter the proc folder of the passed PID and read the first token of the cmdline file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "readFile.h"
#include "readCmd.h"
#include "main.h"

#define LINE_MAX 1024

int readCmd(int pidNum, info* cmdString) {
	
	FILE *fd;
	char *path = NULL;
	char line[LINE_MAX];\

	const char *str = "/proc/cmdline/32768"; //32768 is the max val of a PID
	int pathLength = strlen(str) ;

	//dynamically allocate memory to path based on path length
	path = malloc(sizeof(char) * pathLength);

	//construct dir path by using the pid
	sprintf(path,"/proc/%d/cmdline",pidNum);

	//open the file
	fd = fopen(path,"r");

	if (fd == NULL) {
		puts("File cannot be opened");
		exit(-1);
	}
	else {
		//Assign the first token of the cmdline file to the corresponding string passed as a parameter
		while(fgets(line,LINE_MAX,fd) != NULL)	{
			sscanf(line,"%s",line);
			cmdString->cmd = line;
		}
	}	
	fclose(fd);
	free(path);
	
return 0;
}	
