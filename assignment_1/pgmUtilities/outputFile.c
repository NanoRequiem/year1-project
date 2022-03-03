#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"


int outputImage(Image *inputImage, char *outFile)
{
  //Opening file using user supplied name
  FILE *outputFile = fopen(outFile, "w");

  //Validation check on opening file
  if(outputFile == NULL)
  {
    printf("ERROR: Output File Path Not Found");
    return 11;
  }

  //Writing magic number, comment line, max gray, height and width values
  //to the new file
  //if statement to check that the comment line is present and output it if it's
  //present
  if(inputImage->commentLine == NULL)
  {
    int writtenData = fprintf(outputFile, "%s\n\n%d\n%d %d\n",
                              inputImage->magicNumber,
                              inputImage->maxGray,
                              inputImage->width,
                              inputImage->height);
  }
  else
  {
    int writtenData = fprintf(outputFile, "%s\n%d\n%d %d\n",
                              inputImage->magicNumber,
                              inputImage->commentLine,
                              inputImage->maxGray,
                              inputImage->width,
                              inputImage->height);
  }

  //validating that the output occured
  if(writtenData < 0)
  {
    printf("ERROR: Output Failed")
    return 9;
  }

  //Writing the image data to the output file


  //Closing the output file as we do not need it anymore


  return 0;
}
