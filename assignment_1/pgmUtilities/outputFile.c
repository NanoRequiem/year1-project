#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"


int outputImage(Image *inputImage, char *outFile)
{
  //int to keep track of how much has been written to the output file
  int writtenData;

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
    writtenData = fprintf(outputFile, "%s\n\n%d %d\n%d\n",
                              inputImage->magicNumber,
                              inputImage->width,
                              inputImage->height,
                              inputImage->maxGray);
  }
  else
  {
    writtenData = fprintf(outputFile, "%s\n%s\n\n%d %d\n%d",
                              inputImage->magicNumber,
                              inputImage->commentLine,
                              inputImage->width,
                              inputImage->height,
                              inputImage->maxGray);
  }

  //validating that the output occured
  if(writtenData < 0)
  {
    printf("ERROR: Output Failed");
    return 9;
  }

  //Resetting written data to track imageData outputs
  writtenData = 0;

  //Writing the image data to the output file
  for(int x = 0; x < inputImage->height; x++)
  {
    //writing data from the imageData array to the file
    writtenData = fprintf(outputFile, "%d", inputImage->imageData[x][0]);

    //Sub for loop to write the rest of each array within the 2d array
    for(int y = 1; y < inputImage->width; y++)
    {
      writtenData = fprintf(outputFile, " %d", inputImage->imageData[x][y]);
    }
    //End of current line so print a new line to file
    writtenData = writtenData + fprintf(outputFile, "\n");
  }

  //Closing the output file as we do not need it anymore
  fclose(outputFile);

  return 0;
}
