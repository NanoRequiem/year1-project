HOW TO RUN MY SUBMISSION

make all - Use make all in file directory to make the executables for all files
make <program_name> - Use to make a specific program replacing program_name with the name of the program you wish to reducedCount
make clean - Removes all executable files

HOW TO RUN EACH PROGRAM

The following must be ran in the directory where the object files are stored within
the command line.

pgmEcho - ./pgmEcho inputImage.pgm outputImage.pgm
pgmComp - ./pgmComp inputImage.pgm inputImage.pgm
pgma2b - ./pgma2b inputImage.pgm outputImage.pgm
pgmb2a - ./pgmb2a inputImage.pgm outputImage.pgm
pgmReduce - ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm
pgmTile - ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm
pgmReduce - ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+
