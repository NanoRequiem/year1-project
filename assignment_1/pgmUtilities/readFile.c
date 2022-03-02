#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "readFile.h"

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
int InitImage(Image *inputImage, FILE *data)
{
	return 0;
}
