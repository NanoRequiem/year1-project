#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "imageStructures.h"
#include "pgmReduce.h"
#include "freeData.h"
#include "readFile.h"
#include "outputFile.h"

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
    printf("Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm\n");
    return 0;
  }

  //Call method for reading in command line arguments
  if(validateCmdArguments(4, argc) == 1)
	{
		printf("ERROR: Bad argument count\n");
		return FAIL_BAD_ARGS;
	}

  //Convert argv[2] into and integer to be used
  int factor;

  //Checks if reduction factor is an integer or not
  if(!sscanf(argv[2], "%d", &factor)) {
    printf("ERROR: Miscellaneous (Reduction factor must be an numeric)");
    return FAIL_MISC;
  }

  //Checks if reduction factor is Negative
  if(argv[2] < 0) {
    printf("ERROR: Miscellaneous (Negative reduction factor not accepted)");
    return FAIL_MISC;
  }

  //Create the image structure
	Image *inputImage = (Image *)malloc( sizeof(Image) );


	//Open inputted file
	FILE *data;
	data = fopen(argv[1], "r");

	//Check if the file has been opened and output error message if not
	if(data == NULL)
	{
		printf("ERROR: Bad File Name(%s)\n", argv[1]);

		return FAIL_BAD_FNAME;
	}

  //Check if the file can be read and output error message if not
  if(access(argv[1], R_OK)) {
    printf("ERROR: Miscellaneous (File cannot be read) \n");

    return FAIL_MISC;
  }

	//Calling the InitImage method to initialize the struct
	//The integer readStatus will hold whether the data was
	//read in correctly or not.
	initImage(inputImage);
	int readStatus = readImageHead(inputImage, data);

	//if the data read in was not successful output file name and error code;
	if(readStatus != 0)
	{
		printf("(%s)\n", argv[1]);

		//Close file since we've stopped using it due to error
		fclose(data);

		return readStatus;
	}

	//Close the file since we have read everything we need from it
	fclose(data);

  //Initializes the reduced image struct
  Image *reduce = (Image *)malloc( sizeof(Image));

  //Convert argv[2] into and integer to be used
  //int factor;
  //sscanf(argv[2], "%d", &factor);

  //Calls function to initialise the reduce image Struct's data
  initImage(reduce);
  initReduced(inputImage, reduce, factor);

  //Calls function to reduce the data held within the image struct
  reduceImage(inputImage, reduce, factor);

  //Calling module to output reduced data to a file
	int outStatus = outputImage(reduce, argv[3]);

	//output message if the program fails to output a file
	if(outStatus != 0)
	{
		printf("ERROR: Output Failed (%s)", argv[3]);
		return FAIL_BAD_OUTPUT;
	}

  printf("REDUCED\n");
  return SUCCESS_NO_ERRORS;
}

//initReduced method for initializing the reduced file
int initReduced(Image *inputImage, Image *reduce, int factor)
{
  //Initializes magic number with a 0 character meaning NULL
	reduce->magicNumber[0] = inputImage->magicNumber[0];
	reduce->magicNumber[1] = inputImage->magicNumber[1];

	//Initializes commentLine as NULL
	reduce->commentLine = inputImage->commentLine;

	//Initializes data header variables as default variables
	reduce->maxGray = inputImage->maxGray;

  //Get the new width and heights for the reduced image
  reduce->width = roundNumber(inputImage->width, factor);
  reduce->height = roundNumber(inputImage->height, factor);

	return SUCCESS_NO_ERRORS;
}

//roundNumber method to round the two inputted numbers
int roundNumber(int numb1, int numb2)
{
  int divisor = numb1/numb2;

  if(divisor * numb2 == numb1)
  {
    return divisor;
  }

  else
  {
    return divisor + 1;
  }
}

//reduce method to actually reduce the image
int reduceImage(Image *inputImage, Image *reduced, int factor)
{
  //Variable to count for the reduced image
  int reducedCount = 0;

  //initialize rawImageData for reduced
	long nImageBytes = reduced->width * reduced->height * sizeof(int);
	reduced->rawImageData = (int *) malloc(nImageBytes);

  //Loop through input image and output when the x and y values mod to 0 with factor
  for(int y = 0; y < inputImage->height; y++)
  {

      for(int x = 0; x < inputImage->width; x++)
      {
          //Check if x = 0 and y = 0
          if(x == 0 && y == 0)
          {
              //Correct spot so save this data
              reduced->rawImageData[reducedCount] = inputImage->imageData[y][x];
              //Iterate our reduced counter
              reducedCount++;
          }
          //Check if x = 0 and y mod factor = 0
          else if(x == 0 && y % factor == 0)
          {
              //Correct spot so save this data
              reduced->rawImageData[reducedCount] = inputImage->imageData[y][x];
              //Iterate our reduced counter
              reducedCount++;
          }
          //Check if x mod factor = 0 and y = 0
          else if(x % factor == 0 && y == 0)
          {
              //Correct spot so save this data
              reduced->rawImageData[reducedCount] = inputImage->imageData[y][x];
              //Iterate our reduced counter
              reducedCount++;
          }
          //Check if x mod factor = 0 and y mod factor = 0
          else if(x % factor == 0 && y % factor == 0)
          {
              //Correct spot so save this data
              reduced->rawImageData[reducedCount] = inputImage->imageData[y][x];
              //Iterate our reduced counter
              reducedCount++;
          }
        }
    }

    //Call method to convert rawImageData to imageData so that reduced can be outputted
    rawDataToImageData(reduced);

    return SUCCESS_NO_ERRORS;
}
