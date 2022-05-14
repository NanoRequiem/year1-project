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
			${CC}	${CCFLAGS}	-o pgmEcho	 pgmEcho.c readFile.c outputFile.c freeData.c
			${CC}	${CCFLAGS}	-o pgmComp	 pgmComp.c readFile.c freeData.c
			${CC}	${CCFLAGS}	-o pgma2b	 pgma2b.c readFile.c outputFile.c freeData.c
			${CC}	${CCFLAGS}	-o pgmb2a	 pgmb2a.c readFile.c outputFile.c freeData.c
			${CC}	${CCFLAGS}	-o pgmReduce pgmReduce.c readFile.c outputFile.c freeData.c
			${CC} ${CCFLAGS}  -o pgmTile pgmTile.c readFile.c outputFile.c freeData.c stringManip.c
			${CC}	${CCFLAGS}	-o pgmAssemble	 pgmAssemble.c readFile.c outputFile.c freeData.c -lm

#Second target to make pgmEcho
pgmEcho:
			${CC}	${CCFLAGS}	-o pgmEcho	 pgmEcho.c readFile.c outputFile.c freeData.c

#Third target to make pgmComp
pgmComp:
			${CC}	${CCFLAGS}	-o pgmComp	 pgmComp.c readFile.c freeData.c

#Forth target to make pgma2b
pgma2b:
			${CC}	${CCFLAGS}	-o pgma2b	 pgma2b.c readFile.c outputFile.c freeData.c

#Fifth target to make pgmb2a
pgmb2a:
			${CC}	${CCFLAGS}	-o pgmb2a	 pgmb2a.c readFile.c outputFile.c freeData.c

#Sixth target to make pgmReduce
pgmReduce:
			${CC}	${CCFLAGS}	-o pgmReduce pgmReduce.c readFile.c outputFile.c freeData.c

#Seventh target to make pgmTile
pgmTile:
			${CC} ${CCFLAGS}  -o pgmTile pgmTile.c readFile.c outputFile.c freeData.c stringManip.c

#Eighth target to make pgmAssemble
pgmAssemble:
			${CC}	${CCFLAGS}	-o pgmAssemble	 pgmAssemble.c readFile.c outputFile.c freeData.c -lm

#Nineth target to clean
clean:
				rm pgmEcho pgmComp pgma2b pgmb2a pgmReduce pgmTile pgmAssemble
