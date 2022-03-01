#include <stdio.h>
#include <stdlib.h>
#include <string.h>




//Main method for reading in cmd line arguments
//
//argc = number of command line arguments
//**argv = list of all command line arguments

int main(int argc, char **argv)
{
	//Call method to check the number of cmd line arguements
	//if returns false error the program and exit
	if(validateCmdArguments(3, argc))
	{
		printf("ERROR: Bad argument count");
		return 1;
	}
} 
