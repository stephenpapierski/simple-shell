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
#include <list>

#include "shell.h"

using namespace std;

int main(){
    char command[1024];
    char *argv[64];
    //getcwd(cwd,sizeof(cwd));
    
    while(1){
        cout<<"Stephen's Shell>>";               
        //printf("%s$ ", cwd);
        //cout<<"$ ";
        cin.getline(command,1024); //read in command line
        split(command,argv,' '); //generates argument vector
        process_argument(argv);
    }
    return 0;
}

/**
 * This function handles build in shell functions as well as doing the setup for executing programs
 * @brief Decides how to handle arguments
 * @param[in] argv The argument vector
 */
void process_argument(char **argv){
    static char cwd[1024];
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
        bool background = false;
        if (strcmp(argv[arraySize(argv)-1], "&") == 0){ //checks for & background option
            argv[arraySize(argv)-1] = NULL; //removes & from argument vector
            background = true;
        }
        execute_program(argv, background); //execute program
    }
}

/**
 * Executes a program
 * @param[in]   argv        The argument vector
 * @param[in]   background  Should the program be backgrounded?
 */
void execute_program(char **argv, bool background){
    int status;
    static list<pid_t> children;
    static int programs_backgrounded = 0;
    static int backgrounds_finished = 0;
    pid_t pid = fork(); //returns 0 to the child, childs pid to the parent

    if (pid == -1){
        //fork error
        cout<<"Fork error...\n";
    }else if (pid == 0){
        //child process
        if (execvp(argv[0], argv) == -1)
            printf("%s: command not found\n", argv[0]); 
    }else if (pid > 0){
        //shell process
        for (list<pid_t>::iterator i = children.begin(); i != children.end(); i++){ //iterate through traced pid's
            pid_t killed = waitpid(*i, &status, WNOHANG|WUNTRACED); //reaps any children that are finished
            if (killed >0){
                children.erase(i++); //removes killed children from background list
                backgrounds_finished++;
                printf("[%d] Done\n", backgrounds_finished);
            }
        }
        if (background){
            children.push_back(pid); //add background process to traced children
            programs_backgrounded++;
            printf("[%d] %d\n", programs_backgrounded, pid);
        }
        waitpid(pid, &status, (background) ? WNOHANG : WUNTRACED);
    }
}

//-----------------------------------------------------------------------------------------------------------
//UTILITY FUNCTIONS
//-----------------------------------------------------------------------------------------------------------

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
 * Finds the number of non-null items in an array
 * @param[in]   array   The array to be sized up
 * @return      number of non-null items in array
 */
int arraySize(char **array){
    int i = 0;
    while (array[i] != NULL){
        i++;
    }
    return i;
}
