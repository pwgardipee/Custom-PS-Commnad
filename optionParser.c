//Authors: Peyton Gardipee and Tushar Verma
//CS537 Fall 2018
//File Purpose:
//Use getOpt to parse through the command line. Set the appropriate flags based on their intended default values
//and the options that were set

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "optionParser.h"

#define BASETEN 10

int process(int argc,char* argv[], flag* cmdFlags)
{
        int opt;    //Used by getOpt
        char* end = NULL;

        //Flags from passed in flag struct
        cmdFlags->p = 0;
        cmdFlags->pid = 0;
        cmdFlags->s = 0;
        cmdFlags->U = 1;
        cmdFlags->S = 0;
        cmdFlags->v = 0;
        cmdFlags->c = 1;

        //Using getOpt, parse through command line and set flags
        while ((opt = getopt(argc, argv, "c::v::S::U::s::p:")) != -1) {
                switch (opt) {
                case 'c':
                    //Defaults to true
                    if(optarg == NULL){ 
                        cmdFlags->c = 1;
                    }
                    else if(strcmp(optarg, "-") == 0 ){
                        cmdFlags->c = 0;
                    }
                    break;
                case 'v':
                    //Defaults to false
                    if(optarg == NULL){ 
                        cmdFlags->v = 1;
                    }
                    else if(strcmp(optarg, "-") != 0 ){
                      puts("Invalid input for the 'v' option");
                      exit(-1);
                    }
                    break;
                case 'S':
                    //Defaults to false
                    if(optarg == NULL){ 
                        cmdFlags->S = 1;
                    }
                    else if(strcmp(optarg, "-") != 0 ){
                        puts("Invalid input for the 'S' option");
                        exit(-1);
                    }
                    break;
                case 'U':
                    //Defaults to true
                    if(optarg == NULL){ 
                        cmdFlags->U = 1;
                    }
                    else if(strcmp(optarg, "-") == 0 ){
                        cmdFlags->U = 0;
                    }
                    break;
                case 's':
                    //Defaults to false
                    if(optarg == NULL){ 
                        cmdFlags->s = 1;
                    }
                    else if(strcmp(optarg, "-") != 0 ){
                        puts("Invalid input for the 's' option");
                        exit(-1);
                    }
                    break;
                case 'p':
                    if(optarg == NULL){
                        puts("Invalid input for the 'p' option. Valid argument required.");
                        exit(-1);
                    }
                    else if(strcmp(optarg, "-") == 0 ){
                        puts("Invalid input for the 'p' option");
                        exit(-1);
                    }

                    cmdFlags->p = 1;
                    cmdFlags->pid = strtol(optarg,&end,BASETEN);
                    break;
                default:
                    break;
                }
        }


    return 0;
}
