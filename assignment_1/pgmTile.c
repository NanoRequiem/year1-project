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

  //Call method to check the number of cmd line arguements
  //if returns false error the program and exit
  if(validateCmdArguments(4, argc) == 1)
  {
    printf("ERROR: Bad Argument Count \n");
    return FAIL_BAD_ARGS;
  }

  //Create the image structure
	Image *inputImage = (Image *)malloc( sizeof(Image) );


	//Open inputted file
	FILE *data;
	data = fopen(argv[1], "r");

	//Check if the file has been opened and output error message if not
	if(data == NULL)
	{
		printf("ERROR: Bad File Name (%s) \n", argv[1]);

		return FAIL_BAD_FNAME;
	}

  //Check if the file can be read and output error message if not
  if(access(argv[1], R_OK)) {
    printf("ERROR: Miscellaneous (File cannot be read) \n");

    return FAIL_MISC;
  }

  //Convert argv[2] into and integer to be used
  int factor;

  //Checks if tiling factor is an integer or not
  if(sscanf(argv[2], "%d", &factor) != 1) {
    printf("ERROR: Miscellaneous (Tiling factor must be an numeric)");
    return FAIL_MISC;
  }

  //Checks if reduction factor is Negative
  if(factor <= 0) {
    printf("ERROR: Miscellaneous (Negative tiling factor not accepted)");
    return FAIL_MISC;
  }

	//Calling the InitImage method to initialize the struct
	//The integer readStatus will hold whether the data was
	//read in correctly or not.
	initImage(inputImage);
	int readStatus = readImageHead(inputImage, data);

	//if the data read in was not successful output file name and error code;
	if(readStatus != 0 && readStatus != FAIL_MISC)
	{
		//Output the file name (readFile module outputs the rest of the error message)
		printf("(%s)", argv[1]);

		//Close file since we've stopped using it due to error
		fclose(data);

    //Error value obtained from the read image module
		return readStatus;
	}
  else if(readStatus == FAIL_MISC)
  {
    //Close file since we've stopped using it due to error
		fclose(data);

    //Error value obtained from the read image module
		return readStatus;
  }

	//Close the file since we have read everything we need from it
	fclose(data);

  newImageInit(inputImage, factor);

  //Calling module to output read in data to a file
	outputImage(inputImage, argv[3]);
}

//Initializes the new image structs for the tiled imageStructures
int newImageInit(Image *inputImage, int tileFactor)
{
  //Initialize 2d image list for the output
  Image **outputImages = (Image **)malloc(tileFactor * sizeof(Image));
  for(int z = 0; z < tileFactor; z++)
  {
    outputImages[z] = (Image *)malloc(tileFactor * sizeof(Image));
  }

  for(int x = 0; x < tileFactor; x++)
  {
    for(int y = 0; y < tileFactor; y++)
    {
      //copy magic number from input image
      outputImages[x][y].magicNumber[0] = inputImage->magicNumber[0];
      outputImages[x][y].magicNumber[1] = inputImage->magicNumber[1];

      //copy commentLine from input image
      outputImages[x][y].commentLine = inputImage->commentLine;

      //copy maxGray number from inputImage
      outputImages[x][y].maxGray = inputImage->maxGray;

      //Find and copy new height and width
      outputImages[x][y].height = inputImage->height / tileFactor;
      outputImages[x][y].width = inputImage->width / tileFactor;

      initOutImageData(&outputImages[x][y]);

      getTileData(x * outputImages[x][y].width, y * outputImages[x][y].height, inputImage, &outputImages[x][y]);

      //Calling module to output read in data to a file
      saveRAWData(&outputImages[x][y]);
    	outputImage(&outputImages[x][y], "lmao.pgm");
    }
  }
  return 0;
}

int initOutImageData(Image *outImage)
{
  //Initializing the rows of the 2D array to store the image data
  outImage->imageData = (int**)malloc(outImage->height * sizeof(int*));

  for(int x = 0; x < outImage-> width; x++)
  {
    outImage->imageData[x] = (int *)malloc(outImage-> width * sizeof(int));
  }

  return 0;
}

//Gets the data held within each tileFactor
//XOffset and YOffset to make sure we capture the correct data from the correct area
int getTileData(int XOffset, int YOffset, Image *inputImage, Image *outImage)
{
  //Loops through the width of the data
  for(int x = XOffset; x - XOffset < outImage->width; x++)
  {
    //loops through the height of the data
    for(int y = YOffset; y - YOffset < outImage->height; y++)
    {
      outImage->imageData[x - XOffset][y - YOffset] = inputImage->imageData[x][y];
    }
  }

  return 0;
}
