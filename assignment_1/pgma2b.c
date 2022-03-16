#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "pgma2b.h"
#include "readFile.h"
#include "outputFile.h"

//Main method to read in cmd line arguments and call
//modules to read in files
int main(int argc, char **argv)
{
  //Check that the number of commend line arguments is correct
  if(validateCmdArguments(3, argc) == 1)
  {
    printf("ERROR: Bad argument count\n");
		return 1;
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

		return 2;
	}

	//Calling the InitImage method to initialize the struct
	//The integer readStatus will hold whether the data was
	//read in correctly or not.
	initImage(inputImage, data);
	int readStatus = readImageHead(inputImage, data);

	//if the data read in was not successful output file name and error code;
	if(readStatus != 0)
	{
		printf("(%s)\n", argv[1]);

		//Close file since we've stopped using it due to error
		fclose(data);

		return readStatus;
	}


	//Close the opened file since we don't need it anymore
	fclose(data);

	inputImage->magicNumber[0] = 'P';
	inputImage->magicNumber[1] = '5';

	//Call the module to output binary files
	int outStatus = outputImage(inputImage, argv[2]);

	if(outStatus != 0) {
		printf("ERROR: Output failed");
		return 14;
	}

	//Success message
	printf("CONVERTED\n");
  return 0;
}
