#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "readFile.h"

#define MAGIC_NUMBER_ASCII_PGM 0x3250

//Method to check the cmd line inputs
//
//requiredArguments - The arguments required for the utility
//argc - The actual number of arguments inputted by the user

int validateCmdArguments(int requiredArguments, int argc)
{
	if(requiredArguments != argc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//Method to initialize the image data
int initImage(Image *inputImage, FILE *data)
{
	//Initializes magic number with a 0 character meaning NULL
	inputImage->magicNumber[0] = '0';
	inputImage->magicNumber[1] = '0';

	//Initializes commentLine as NULL
	inputImage->commentLine = NULL;

	//Initializes data header variables as default variables
	inputImage->height = 0;
	inputImage->width = 0;
	inputImage->maxGray = 255;

	return 0;
}

//Method to initialize and read in the image Header information
//inputImage - The struct where we are going to save the file's data
//data - The file that the data is being read from
int readImageHead(Image *inputImage, FILE *data)
{
	//Initializes magicNumber
	unsigned short *magic_Number = (unsigned short *) inputImage->magicNumber;

	//Saves magicNumber from file
	inputImage->magicNumber[0] = getc(data);
	inputImage->magicNumber[1] = getc(data);

	//Checks if magic numebr is correct
	if (*magic_Number != MAGIC_NUMBER_ASCII_PGM)
	{
		printf("ERROR: Bad Magic Number");
		return 1;
	}

	//Used to scan for whitespace
	int scanCount = fscanf(data, " ");

	//Next char to check for a comment line. If it's there save it
	//If not put character back and continue
	char nextChar = getc(data);
	if(nextChar == '#')
	{
		//Initializing commentLine
		inputImage->commentLine = (char *) malloc(128);

		//Capturing input commentLine
		char *comment = fgets(inputImage->commentLine, 128, data);
		printf("%s", inputImage->commentLine);

		//Checking if comment line has been read Null means failure
		if(comment == NULL)
		{
			printf("ERROR: Bad Comment Line");
			return 4;
		}
	}
	else
	{
		ungetc(nextChar, data);
	}

	//Reads in header information
	scanCount = fscanf(data, " %u %u %u",
											&(inputImage->width),
											&(inputImage->height),
											&(inputImage->maxGray));

	//Validation checks for the width and heightvalues
	if(inputImage->width < 1 || inputImage->width > 65536 ||
		inputImage->height < 1 || inputImage->height > 65536)
	{
		printf("ERROR: Bad Dimensions");
		return 5;
	}

	//Validation check for maxGray value
	if(inputImage->maxGray != 255)
	{
		printf("ERROR: Bad Max GrayValue ");
		return 6;
	}
	return 0;
}

//Method to read in the specific values of each point of the image
//inputImage - The struct where we are going to save the file's data
//data - The file that the data is being read from
int readImageData(Image *inputImage, FILE *data)
{
	//Initializing the rows of the 2D array to store the image data
	inputImage->imageData = (char**)malloc(inputImage->height * sizeof(char*));

	//For loop to initialize the columns of the array
	for(int x = 0; x < inputImage->height; x++)
	{
		inputImage->imageData[x] = (char*)malloc(inputImage->width * sizeof(char));
	}

	return 0;
}
