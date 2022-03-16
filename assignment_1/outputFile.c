#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "freeData.h"
#include "outputFile.h"


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
    freeImage(inputImage);
    return 11;
  }

  //Writing magic number, comment line, max gray, height and width values
  //to the new file
  //if statement to check that the comment line is present and output it if it's
  //present
  if(inputImage->commentLine == NULL)
  {
    writtenData = fprintf(outputFile, "%c%c\n\n%d %d\n%d\n",
                              inputImage->magicNumber[0],
                              inputImage->magicNumber[1],
                              inputImage->width,
                              inputImage->height,
                              inputImage->maxGray);
  }
  else
  {
    writtenData = fprintf(outputFile, "%c%c\n%s\n\n%d %d\n%d",
                              inputImage->magicNumber[0],
                              inputImage->magicNumber[1],
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

  unsigned short *magic_Number = (unsigned short *) inputImage->magicNumber;

  //Checking if the image is an ASCII file
  if(*magic_Number == 0x3250)
  {
    //Calling the function to output ascii data
    writeASCIIData(inputImage, outputFile);
  }
  else if(*magic_Number == 0x3550)
  {
    //Calling function to output raw data
    writeRAWData(inputImage, outputFile);
  }

  //Closing the output file as we do not need it anymore
  fclose(outputFile);

  return 0;
}

int writeASCIIData(Image *inputImage, FILE *outputFile)
{
  int writtenData = 0;

  //Writing the image data to the output file
  for(int x = 0; x < inputImage->height; x++)
  {
    //writing data from the imageData array to the file
    writtenData = fprintf(outputFile, "%u", inputImage->imageData[x][0]);

    //Check how many digits each number is to add the correct amount of spaces after each number
    if(inputImage->imageData[x][0] < 10)
    {
      writtenData = fprintf(outputFile, "  ");
    }
    else if(inputImage->imageData[x][0] < 100)
    {
      writtenData = fprintf(outputFile, " ");
    }

    //Sub for loop to write the rest of each array within the 2d array
    for(int y = 1; y < inputImage->width; y++)
    {
      //Check how many digits each number is to add the correct amount of spaces before each number
      if(inputImage->imageData[x][y] < 10)
      {
        writtenData = fprintf(outputFile, "  ");
      }
      else if(inputImage->imageData[x][y] < 100)
      {
        writtenData = fprintf(outputFile, " ");
      }

      writtenData = fprintf(outputFile, "%u ", inputImage->imageData[x][y]);
    }
    //End of current line so print a new line to file
    writtenData = writtenData + fprintf(outputFile, "\n");
  }

  //success so return 0
  return 0;
}

int writeRAWData(Image *inputImage, FILE *outputFile)
{
  //loops through 
  for(int x = 0; x < inputImage->height * inputImage->width; x++)
  {
    //Converts the saved data into a character
    char data = inputImage->rawImageData[x];
    //Outputs raw character data to file and checks it has been written
    if(fwrite(&data, 1, 1, outputFile) != 1)
    {
      printf("ERROR: Binary write failed");
      return 16;
    }
  }

  //Successful write so return 0
  return 0;
}
