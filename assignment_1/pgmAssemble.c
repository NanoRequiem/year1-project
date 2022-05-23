#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "imageStructures.h"
#include "readFile.h"
#include "outputFile.h"
#include "pgmAssemble.h"

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
    printf("Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+");
    return 0;
  }

  //Call method to check the number of cmd line arguements
  //if returns false error the program and exit
  if(argc < 6)
  {
    printf("ERROR: Bad Argument Count \n");
    return FAIL_BAD_ARGS;
  }

  int numbOfImage = (argc - 4) / 3;
  int fileNameIndex = 6;

  Image **ImageList = (Image **)malloc(numbOfImage * sizeof(Image));

  for(int x = 0; x < numbOfImage; x++)
  {
    ImageList[x] = (Image *)malloc(sizeof(Image));
  }

  for(int x = 0; x < sqrt(numbOfImage); x++)
  {
    for(int y = 0; y < sqrt(numbOfImage); y++)
    {
      //Open inputted file
      FILE *data;
      data = fopen(argv[fileNameIndex], "r");

      //Check if the file has been opened and output error message if not
      if(data == NULL)
      {
        printf("ERROR: Bad File Name (%s) \n", argv[fileNameIndex]);

        return FAIL_BAD_FNAME;
      }

      //Check if the file can be read and output error message if not
      if(access(argv[fileNameIndex], R_OK)) {
        printf("ERROR: Miscellaneous (File cannot be read) \n");

        return FAIL_MISC;
      }

      fileNameIndex = fileNameIndex + 3;
    }
  }

  printf("ASSEMBLED");
  return SUCCESS_NO_ERRORS;
}

int initImageList(Image **ImageList, int numbOfImage)
{
  *ImageList = (Image *)malloc(numbOfImage * sizeof(Image));

  for(int x = 0; x < numbOfImage; x++)
  {
    ImageList[x] = (Image *)malloc(sizeof(Image));
  }

  return 0;
}
