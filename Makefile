#Compile to use
CC=g++
#Compiler flags
CFLAGS=-Wall

shell.o: shell.cpp
	$(CC) $(CFLAGS) shell.cpp

clean:
	rm a.out
