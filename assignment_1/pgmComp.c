#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "readFile.h"
#include "pgmComp.h"

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
  initImage(firstImage);
	int readStatus = readImageHead(firstImage, firstData);

  //if the data read in was not successful output file name and error code;
	if(readStatus != 0)
	{
		printf("(%s)\n", argv[1]);

		//Close file since we've stopped using it due to error
		fclose(firstData);

		return readStatus;
	}

  //Close first image since we've finished with the data
  fclose(firstData);

  //open the second image
  FILE *secondData;
  secondData = fopen(argv[1], "r");

  //check the second image has been opened
  if(firstData == NULL)
	{
		printf("ERROR: Bad File Name(%s)\n", argv[2]);

		return 2;
	}

  //Read in data for the second image
  initImage(secondImage);
	readStatus = readImageHead(secondImage, secondData);

  //if the data read in was not successful output file name and error code;
	if(readStatus != 0)
	{
		printf("(%s)\n", argv[2]);

		fclose(secondData);


		return readStatus;
	}

  //Call method to compare the data saved in both images
  int compStatus = Comp(firstImage, secondImage);

  //if the comp method returns a success that meand the program is successful
  //and should output the correct string to indicate.
  if(compStatus == 0)
  {
    printf("IDENTICAL\n");
    return 0;
  }

  else
  {
    printf("DIFFERENT\n");
    return 0;
  }
}


//Method to compare the data from each then output if it was successful or not
//firstImage - data stored for the first image inputted
//secondImage - data stored for the second image inputted
int Comp(Image *firstImage, Image *secondImage)
{
  //Compares magic numbers of both images and returns false if they're
  //different
  if(firstImage->magic_Number != secondImage->magic_Number)
  {
    //Returns 1 signifying the files are logically different
    return 1;
  }

  //Compares height and width of both images and returns false if they're
  //different
  else if(firstImage->width != secondImage->width ||
          firstImage->height != secondImage->height)
  {
    //Returns 1 signifying the files are logically different
    return 1;
  }

  //Compares max gray of both images and returns false if they're
  //different
  else if(firstImage->maxGray != secondImage->maxGray)
  {
    //Returns 1 signifying the files are logically different
    return 1;
  }

  //Loops through all of the image data and compares each point in the array
  //If any of the points are different return false
  int sameData = 1; //sameData variable for checking that the data is the same after the loop has finished

  for(int x = 0; x < firstImage->height; x++)
  {
    for(int y = 0; y < firstImage->width; y++)
    {
      if(firstImage->imageData[x][y] != secondImage->imageData[x][y])
      {
        //Set sameData to 1 to indicate failure and break the loop since
        //we do not need to check every value.
        sameData = 0;
        break;
      }
    }
  }

  //Check if the loop failed or not using the sameData variable
  if(sameData == 0)
  {
    //Returns 1 signifying the files are logically different
    return 1;
  }

  return 0;
}
