#
#pgmUtilities
#Makefile
#Brooklyn Mcswiney
#

#Macro for compiler name
CC=gcc
#Macro for compile flags
CCFLAGS=-g -std=c99 -Wall -Werror
#The set of subordinate subroutines
MODULES=readFile.o outputFile.o imageStructures.h
#The set of main subroutines
MAINS=pgmEcho.o pgmComp.o
#The set of executables
TARGETS=pgmEcho pgmComp

#First target to create executables for all files
#regardless of dependencies
all:
			${CC}	${CCFLAGS}	-o pgmEcho	pgmEcho.c readFile.c outputFile.c
			${CC}	${CCFLAGS}	-o pgmComp	pgmComp.c readFile.c

#Second target to clean
clean:
				rm pgmEcho pgmComp
