#
#pgmUtilities
#Makefile
#Brooklyn Mcswiney
#

#Macro for compiler name
CC=gcc
#Macro for compile flags
CCFLAGS=-g -std=c99 -Wall -Werror

#First target to create executables for all files
#regardless of dependencies
all:
			${CC}	${CCFLAGS}	-o pgmEcho	pgmEcho.c readFile.c outputFile.c freeData.c
			${CC}	${CCFLAGS}	-o pgmComp	pgmComp.c readFile.c freeData.c
			${CC}	${CCFLAGS}	-o pgma2b	pgma2b.c readFile.c outputFile.c freeData.c
			${CC}	${CCFLAGS}	-o pgmb2a	pgmb2a.c readFile.c outputFile.c freeData.c

#Second target to clean
clean:
				rm pgmEcho pgmComp pgma2b pgmb2a
				rm temp*.pgm
