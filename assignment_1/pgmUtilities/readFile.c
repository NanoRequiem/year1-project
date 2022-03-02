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

//Method to initialize and check the values found in the Image struct
//inputImage - The struct where we are going to save the file's data
//data - The file that the data is being read from
int ReadImage(Image *inputImage, FILE *data)
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

	//Next char to check for a comment line. If it's there save it
	//If not put character back and continue
	char nextChar = getc(data)

	return 0;
}
