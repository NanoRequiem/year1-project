#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readFile.h"
#include "imageStructures.h"

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
