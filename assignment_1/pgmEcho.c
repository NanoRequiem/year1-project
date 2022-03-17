#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "readFile.h"
#include "outputFile.h"
#include "pgmEcho.h"

#define SUCCESS_NO_ERRORS 0
#define FAIL_BAD_ARGS 1
#define FAIL_BAD_FNAME 2

//Main method for reading in cmd line arguments
//
//argc = number of command line arguments
//**argv = list of all command line arguments

int main(int argc, char **argv)
{
	//If no arguments are supplied output the correct arguments
  if(argc == 1)
  {
    printf("Usage: ./pgmEcho inputImage.pgm outputImage.pgm\n");
    return 0;
  }

	//Call method to check the number of cmd line arguements
	//if returns false error the program and exit
	if(validateCmdArguments(3, argc) == 1)
	{
		printf("ERROR: Bad argument count\n");
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
		printf("ERROR: Bad File Name(%s)\n", argv[1]);

		return FAIL_BAD_FNAME;
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

	//Calling module to output read in data to a file
	int outStatus = outputImage(inputImage, argv[2]);

	//output message if the program fails to output a file
	if(outStatus != 0)
	{
		printf("(%s)\n", argv[1]);
		return outStatus;
	}
	//Output message if the program successfully executes
	printf("ECHOED\n");
	return SUCCESS_NO_ERRORS;
}
