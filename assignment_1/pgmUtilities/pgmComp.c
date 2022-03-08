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
  FILE *firstData;
	firstData = fopen(argv[1], "r");
  //Check the first image file has been opened
  if(firstData == NULL)
	{
		printf("ERROR: Bad File Name(%s)\n", argv[1]);

		return 2;
	}

  //read in data for the first image
  initImage(firstImage, firstData);
	int readStatus = readImageHead(firstImage, firstData);

  //if the data read in was not successful output file name and error code;
	if(readStatus != 0)
	{
		printf("(%s)\n", argv[1]);

		//Close file since we've stopped using it due to error
		fclose(firstData);

		return readStatus;
	}

  //open the second image
  FILE *secondData;
  secondData = fopen(argv[1], "r");

  //check the second image has been opened
  if(firstData == NULL)
	{
		printf("ERROR: Bad File Name(%s)\n", argv[1]);

		return 2;
	}

  //Read in data for the second image
  initImage(secondImage, secondData);
	readStatus = readImageHead(firstImage, firstData);

  //if the data read in was not successful output file name and error code;
	if(readStatus != 0)
	{
		printf("(%s)\n", argv[1]);

		//Close both files since we've stopped using it due to error
		fclose(secondData);
    fclose(firstData);

		return readStatus;
	}

  //Call method to compare the data saved in both images
  Comp(firstImage, secondImage);
}


//Method to compare the data from each then output if it was successful or not
//firstImage - data stored for the first image inputted
//secondImage - data stored for the second image inputted
int Comp(Image *firstImage, Image *secondImage)
{

}
