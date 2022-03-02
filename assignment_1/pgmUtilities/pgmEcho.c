#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	
}
