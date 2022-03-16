#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "pgmReduce.h"
#include "freeData.h"
#include "readFile.h"
#include "outputFile.h"

//Main method for reading in cmd line arguments
//
//argc = number of command line arguments
//**argv = list of all command line arguments

int main(int argc, char **argv)
{
    //Call method for reading in command line arguments
    if(validateCmdArguments(4, argc) == 1)
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

	//Close the file since we have read everything we need from it
	fclose(data);

    //Initializes the reduced image struct
    Image *reduce = (Image *)malloc( sizeof(Image));

    //Convert argv[2] into and integer to be used
    int factor;
    sscanf(argv[2], "%d", &factor);

    //Calls function to initialise the reduce image Struct's data
    initReduced(inputImage, reduce, factor);
}

//initReduced method for initializing the reduced file
int initReduced(Image *inputImage, Image *reduce, int factor)
{
    //Initializes magic number with a 0 character meaning NULL
	reduce->magicNumber[0] = inputImage->magicNumber[0];
	reduce->magicNumber[1] = inputImage->magicNumber[0];

	//Initializes commentLine as NULL
	reduce->commentLine = inputImage->commentLine;

	//Initializes data header variables as default variables
	reduce->maxGray = inputImage->maxGray;

    //Get the new width and heights for the reduced image
    reduce->width = inputImage->width/factor + 1;
    reduce->height = inputImage->height/factor + 1;

    printf("%d\n", reduce->width);
    printf("%d\n", reduce->height);

	return 0;
}

//reduce method to actually reduce the image
int reduce(Image *inputImage, Image *reduced, int factor)
{
    return 0;
}