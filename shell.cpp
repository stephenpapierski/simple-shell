/**
 * @file shell.cpp
 * @author Stephen Papierski <stephenpapierski@gmail.com>
 * @version 0.1
 * @date 22 February 2015
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

#include "shell.h"

using namespace std;

int main(){
    char command[1024];
    char *argv[64];
    char cwd[1024];
    //getcwd(cwd,sizeof(cwd));
    
    while(1){
        cout<<"Stephen's Shell>>";               
        //printf("%s$ ", cwd);
        //cout<<"$ ";
        cin.getline(command,1024); //read in command line
        split(command,argv,' '); //generates argument vector

        if (argv[0] == NULL){
            //do nothing
        }else if (strcmp(argv[0],"exit") == 0){         //exit
            exit(EXIT_SUCCESS);
        }else if (strcmp(argv[0],"cd") == 0){           //cd
            if (chdir(argv[1]) != 0)
                cout<<"No such file or directory\n";
        }else if (strcmp(argv[0], "pwd") == 0){         //pwd
            if (getcwd(cwd,sizeof(cwd)) != NULL)
                printf("%s\n", cwd);
        }else if (strcmp(argv[0], "version") == 0){     //version
            cout<<version;
        }else{
            execute_program(argv);                      //execute program
        }

    }
    return 0;
}

/**
 * Splits a given string into an array based on the delimeter
 * @param[in]   line    The string to be parsed
 * @param[out]  split   The array of split segments
 * @param[in]   delim   The splitting delimeter
 */
void split(char *line, char **split, char delim){
    while (*line != '\0'){ //if not EOL
        while (*line == delim) //replace spaces with \0
            *line++ = '\0'; 
        *split++ = line; //store address of argument
        while (*line != '\0' && *line != delim && *line != '\t' && *line != '\n')
            line++;
    }
    *split = '\0'; //end of argument splittor
    return;
}

/**
 * Executes a program
 */
void execute_program(char **argv){
    int status;
    pid_t pid = fork();

    if (pid == -1){
        //fork error
        cout<<"Fork error...\n";
    }else if (pid == 0){
        //child process
        if (execvp(argv[0], argv) == -1)
            printf("%s: command not found\n", argv[0]); 
    }else if (pid > 0){
        //shell process
        waitpid(-1, &status, WUNTRACED);
    }
}
