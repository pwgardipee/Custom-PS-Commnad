//Authors: Peyton Gardipee and Tushar Verma
//CS537 Fall 2018
//File Purpose:
//Call functions that set up all information about the PIDS based on user input at the command line. Based on the command line options
//that are set by the user, display the collected information 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "optionParser.h"
#include "setInfo.h"
#include "main.h"
#include "listProcesses.h"
#include "isPidValid.h"
#include "readCmd.h"

#define BUFFSIZE 1024 

int main(int argc,char* argv[])
{
        int* userProcesses;// 
        int* arraySize;
        int currPID;

        //flag is a structure containing ints for each relevent command line option(and an int for the PID argument of the p option)
        flag* cmdFlags = (flag*)malloc(sizeof(flag));

        //Sets the flags based on the command line arguments
        process(argc,argv,cmdFlags);

	//infoHolder is a structure containing 
	info* infoHolder = (info*)malloc(BUFFSIZE*sizeof(info));

        arraySize = (int*)calloc(BUFFSIZE, sizeof(int));
		
        // at this point userProcess points to a list of all user pids        
        userProcesses = listprocess(arraySize);

        if(cmdFlags->p){
                //Check PID for validity
                if (isPidValid(cmdFlags->pid) == 0) {
                        printf("%d is not a valid pid. Not found in the proc dir\n",cmdFlags->pid);
                        exit(EXIT_FAILURE);
                }
                // now if the user enter a p flag it just is list of 1 pid, which is the pid entered
                userProcesses[0] = cmdFlags->pid;
                *arraySize = 1;
        }
      
        // iterate through the list of all pids depending on the above logic  
        for (int i =0; i<*arraySize;i = i + 1) {
        
                currPID = userProcesses[i];

                //readCmd(strtol(argv[2],&end,10));
                readCmd(currPID, infoHolder);

                //Read teh stat and statm files
                infoHolder->state = malloc(sizeof(char)*1024);
                setInfo(currPID,infoHolder);
                
                printf("%d: ",currPID);        

                //Concatenate state on to output 
                if(cmdFlags->s){
                        printf(" %s ",infoHolder->state);    
                }

                //Concatenate user time on to output 
                if(cmdFlags->U){
                        printf(" uTime=%s ",infoHolder->uTime);    
                }

                //Concatenate system time on to output 
                if(cmdFlags->S){
                        printf(" sTime=%s ",infoHolder->sTime);    
                }

                //Concatenate virtual memory on to output 
                if(cmdFlags->v){
                        printf(" vMem=%s ",infoHolder->vMem);    
                }

                //Concatenate system time on to output 
                if(cmdFlags->c){
                        printf(" cmd=%s ",infoHolder->cmd);
                }

                printf("\n");
                free(infoHolder->state);
        }

        free(cmdFlags);
        free(infoHolder);

        return 0;
}

