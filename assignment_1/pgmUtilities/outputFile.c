#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"


int outputImage(Image *inputImage, char *outFile)
{
  //Opening file using user supplied name
  FILE *outputFile = fopen(outFile, "w");

  //Validation check on opening file

  //Writing magic number, comment line, max gray, height and width values
  //to the new file

  //validating that the output occured

  //Writing the image data to the output file

  //Closing the output file as we do not need it anymore

  
  return 0;
}
