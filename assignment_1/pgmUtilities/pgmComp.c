#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "readFile.h"

//Main method for reading in cmd line arguments and Calling
//readFile methods.
//
//argc = number of command line arguments
//**argv = list of all command line arguments
//argv[1] = first pgm file
//argv[2] = second pgm file to be compared to first

int main(int argc, char **argv)
{
  //Check that enough command line arguments have been supplied
  //if not output error
  if(validateCmdArguments(3, argc) == 1)
  {
    printf("ERROR: Bad argument count\n");
		return 1;
  }

  //initialize the first image object
  Image *firstImage = (Image *)malloc( sizeof(Image) );

  //Initialize the second image object to be compared to
  Image *secondImage = (Image *)malloc ( sizeof(Image) );

  //open the first image file

  //Check the first image file has been opened


  //read in data for the first image

  //open the second image


  //check the second image has been opened

  //Read in data for the second image

}
