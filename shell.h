#ifndef SHELL_H
#define SHELL_H

//-------------------------------------------------------------------
//VARIABLES
//-------------------------------------------------------------------
char version[] = "Simple Shell 0.1\nCopyright 2015 Stephen Papierski\nThis is free software.\nThere is NO WARRANTY, to the extent permitted by law.\nWritten by Stephen Papierski <stephenpapierski@gmail.com>\n";

//------------------------------------------------------------------
//FUNCTION PROTOTYPES
//------------------------------------------------------------------
int main(void);
void process_argument(char **);
void execute_program(char **, bool);
void split(char *, char **, char);
int arraySize(char **);

#endif
