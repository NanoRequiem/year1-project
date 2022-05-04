#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "imageStructures.h"
#include "pgma2b.h"
#include "readFile.h"
#include "outputFile.h"

#define SUCCESS_NO_ERRORS 0
#define FAIL_BAD_ARGS 1
#define FAIL_BAD_FNAME 2
#define FAIL_BAD_OUTPUT 9
#define FAIL_MISC 100

//Main method to read in cmd line arguments and call
//modules to read in files
int main(int argc, char **argv)
{
  //If no arguments are supplied output the correct arguments
  if(argc == 1)
  {
    printf("Usage: ./pgma2b inputImage.pgm outputImage.pgm\n");
    return 0;
  }

  //Check that the number of commend line arguments is correct
  if(validateCmdArguments(3, argc) == 1)
  {
    printf("ERROR: Bad Argument Count ");
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
		printf("ERROR: Bad File Name (%s) ", argv[1]);

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
    //Output the file name (readFile module outputs the rest of the error message)
		printf("(%s)\n", argv[1]);

		//Close file since we've stopped using it due to error
		fclose(data);

    //Error value obtained from the read image module
		return readStatus;
	}

	//Close the opened file since we don't need it anymore
	fclose(data);

  //Check that the inputted image is an ascii image
  if(inputImage->magicNumber[1] == '5')
  {
    printf("ERROR: Miscellaneous (binary File was inputted when ASCII file required)\n");

    return FAIL_MISC;
  }

	inputImage->magicNumber[0] = 'P';
	inputImage->magicNumber[1] = '5';

	//Call the module to output binary files
	int outStatus = outputImage(inputImage, argv[2]);

	if(outStatus != 0) {
		printf("ERROR: Output failed (%s)\n", argv[2]);
		return FAIL_BAD_OUTPUT;
	}

	//Success message
	printf("CONVERTED\n");
  return SUCCESS_NO_ERRORS;
}
