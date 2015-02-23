#ifndef SHELL_H
#define SHELL_H

//-------------------------------------------------------------------
//VARIABLES
//-------------------------------------------------------------------
char version[] = "Stephen's Shell 0.1\nCopyright 2015 Stephen Papierski\nThis is free software.\nThere is NO WARRANTY, to the extent permitted by law.\nWritten by Stephen Papierski <stephenpapierski@gmail.com>\n";

//------------------------------------------------------------------
//FUNCTION PROTOTYPES
//------------------------------------------------------------------
int main(void);
void process_argument(char **);
void execute_program(char **, bool);
void clean_argv(char **, int);
void split(char *, char **, char);
int arraySize(char **);
int index(char **, char *);
void print_array(char **);

#endif
