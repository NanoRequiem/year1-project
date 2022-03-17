#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "freeData.h"

#define SUCCESS 0

//Module to free data should any part fail
int freeImage(Image *inputImage)
{
	//Checks if each piece of data within the struct is allocated
	//if it is allocated the data is freed
	//First checks magicNumber
	if(inputImage->magicNumber != NULL)
	{
		free(inputImage->magicNumber);
	}
	//Checks magic_Number
	if(inputImage->magic_Number != NULL)
	{
		free(inputImage->magic_Number);
	}
	//Checks commentLine
	if(inputImage->commentLine != NULL)
	{
		free(inputImage->commentLine);
	}
	//Checks for image data then uses a for loop to free data backwards
	if(inputImage->imageData != NULL)
	{
		for(int x = inputImage->height; x >= 0; x--)
		{
			free(inputImage->imageData[x]);
		}
		free(inputImage->imageData);
	}

	return SUCCESS;
}
