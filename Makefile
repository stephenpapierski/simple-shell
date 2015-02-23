#Compiler to use
CC=g++
#Compiler flags
CFLAGS=-Wall

shell.o: shell.cpp
	$(CC) $(CFLAGS) -o ss shell.cpp

clean:
	rm -f a.out ss
