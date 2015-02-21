/**
 * @file shell.cpp
 * @author Stephen Papierski <stephenpapierski@gmail.com>
 * @version 0.1
 */
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "shell.h"

using namespace std;

int main(){
    char command[1024];
    char *argv[64];
    
    //while (1)
    while(1){
        cout<<"$ ";
        cin.getline(command,1024); //read in command line
        split(command,argv); //generates argument vector

        execute_program(argv); //execute program
    }
    return 0;
}

/**
 * Processes command line argument and generates the argument vector
 */
void split(char *line, char **argv){
    while (*line != '\0'){ //if not EOL
        while (*line == ' ') //replace spaces with \0
            *line++ = '\0'; 
        *argv++ = line; //store address of argument
        while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n')
            line++;
    }
    *argv = '\0'; //end of argument vector
}

/**
 * Executes a program
 */
void execute_program(char **argv){
    int status;
    pid_t pid = fork();

    if (pid == -1){
        //fork error
        cout<<"Fork error...";
    } else if (pid == 0){
        //child process
        execv(*argv, argv);
    } else if (pid > 0){
        waitpid(-1, &status, WUNTRACED);
        //shell process
    }
}
