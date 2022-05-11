#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "imageStructures.h"
#include "readFile.h"
#include "outputFile.h"
#include "pgmTile.h"

#define SUCCESS_NO_ERRORS 0
#define FAIL_BAD_ARGS 1
#define FAIL_BAD_FNAME 2
#define FAIL_BAD_OUTPUT 9
#define FAIL_MISC 100

//Main method for reading in cmd line arguments
//
//argc = number of command line arguments
//**argv = list of all command line arguments
int main(int argc, char **argv)
{
  //If no arguments are supplied output the correct arguments
  if(argc == 1)
  {
    printf("Usage: ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm");
    return 0;
  }
}
