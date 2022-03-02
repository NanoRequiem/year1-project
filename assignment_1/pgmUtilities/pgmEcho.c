#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "readFile.h"

//Main method for reading in cmd line arguments
//
//argc = number of command line arguments
//**argv = list of all command line arguments

int main(int argc, char **argv)
{
	//Call method to check the number of cmd line arguements
	//if returns false error the program and exit
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
	InitImage(inputImage, data);
}
