# CS537P1
Intro to Operating Systems, Programming Assignment 1

This project is a custom replacement for the linux ps command. You are able to get a list of all user processes or any one specified process. To get the list of all user processes, do not include a -p<pid> option in the command line. To get any pid information, include -p<pid> in the command line. Either of these options can be modified by choosing any combination of these options:
-c to hide the command line string 
-U- to hide the user time spent
-S to see the system time spent
-s to see the state 
-v to see the virtual memory


Our whole program was designed with modularization in mind. Note only did this help us in reducing bugs in the development stage, but it also helped us with testing and with code readability. Perhaps there are ways to write a program with similar functionality and with less lines of code or less files, but it would be harder to follow the code intuitively. 

The command line arguments are checked both by the OptArg built in functionality and also custom error checking after optArg returns its information. Together this results in a robust program which will not be affected by trying to open nonexistant files, etc.

All in all, modularization was the priority in our coding style and program structure. That, in turn, will allow reuse in the future and readability and proper functionality now. 
