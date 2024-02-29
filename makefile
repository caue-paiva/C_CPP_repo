# makefile model num 1

#compiler and its args, -O0 is for no optimization (useful for debuggind and valgrind)
CC=gcc
CFLAGS= -Wall -g -std=c99 -O0

#debugger and its args
CDB=gdb
DBFLAGS= 

#binary executable name
EXEC=main.out



all: 

run:

#compile and run using valgrind to check for memory leaks
valrun: 
   make run && valgrind --leak-check=full --track-origins=yes ./${EXEC}

clear:

