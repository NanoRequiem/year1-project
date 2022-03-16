#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "freeData.h"
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
	if (*magic_Number != 0x3250 && *magic_Number != 0x3550)
	{
		printf("ERROR: Bad Magic Number");

		freeImage(inputImage);

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

			freeImage(inputImage);

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

	//Validation check for the scan count to ensure everything has been read
	if(scanCount != 3)
	{
		printf("ERROR: Bad header data");

		freeImage(inputImage);

		return 12;
	}

	//Validation checks for the width and heightvalues
	if(inputImage->width < 1 || inputImage->width > 65536 ||
		inputImage->height < 1 || inputImage->height > 65536)
	{
		printf("ERROR: Bad Dimensions");

		freeImage(inputImage);

		return 5;
	}

	//Validation check for maxGray value
	if(inputImage->maxGray != 255)
	{
		printf("ERROR: Bad Max GrayValue ");
		return 6;
	}

	//Initialise imageDataStatus to keep track of whether reading in data was successful
	int imageDataStatus = -1;

	//If file is ascii call the readASCIIData function
	if(*magic_Number == 0x3250)
	{
		imageDataStatus = readASCIIData(inputImage, data);
	}

	//If file is a binary file call the readASCIIData function
	else if(*magic_Number == 0x3550)
	{
		imageDataStatus = ReadRAWData(inputImage, data);
	}

	return imageDataStatus;
}

//Method to read in the specific values of each point of the image
//inputImage - The struct where we are going to save the file's data
//data - The file that the data is being read from
int readASCIIData(Image *inputImage, FILE *data)
{
	//Initializing the rows of the 2D array to store the image data
	inputImage->imageData = (int**)malloc(inputImage->height * sizeof(int*));

	//For loop to initialize the columns of the array
	for(int x = 0; x < inputImage->height; x++)
	{
		inputImage->imageData[x] = (int*)malloc(inputImage->width * sizeof(int));
	}

	//For loop that goes through all of the image's data and saves it
	//First for loop goes through the rows of the 2d array where as the
	//second for loop goes through the columns of the 2d array.
	for(int y = 0; y < inputImage->height; y++)
	{
		for(int x = 0; x < inputImage-> width; x++)
		{
			//Captures data from file for the imageData 2d array
			int scanCount = fscanf(data, " %u",&(inputImage->imageData[y][x]));
			//Validate that correct amount of data was read in
			if(scanCount != 1)
			{
				printf("ERROR: Bad Data formatting");

				freeImage(inputImage);

				return 13;
			}

			//Validation check on the captured data
			if(inputImage->imageData[y][x] < 0 ||
					inputImage->imageData[y][x] > 255)
			{
				printf("ERROR: Bad Data");

				freeImage(inputImage);

				return 8;
			}
		}
	}

	//Converts and stores current stored data as raw binary data
	int rawStatus = saveRAWData(inputImage);

	if(rawStatus != 0)
	{
		printf("ERROR: Bad Raw Data");

		freeImage(inputImage);

		return 15;
	}

	return 0;
}

int saveRAWData(Image *InputImage)
{
	//initialize rawImageData
	long nImageBytes = InputImage->width * InputImage->height * sizeof(int);
	InputImage->rawImageData = (int *) malloc(nImageBytes);

	//count value for rawImageData
	int rawImageCount = 0;

	for(int y = 0; y < InputImage->height; y++)
	{
		for(int x = 0; x <InputImage->width; x++)
		{
			InputImage->rawImageData[rawImageCount] = (int) InputImage->imageData[y][x];
			rawImageCount++;
		}
	}

	return 0;
}

int ReadRAWData(Image *inputImage, FILE *data)
{
	//Skips blank space line so that the data can be read
	fscanf(data, " ");

	//initialize rawImageData
	long nImageBytes = inputImage->width * inputImage->height * sizeof(int);
	inputImage->rawImageData = (int *) malloc(nImageBytes);

	//Loops through list and takes in char value for each position in the list
	for(int x = 0; x < inputImage->height * inputImage->width; x++)
	{	
		//reads in data from the binary file
		int scanCount = fread(&(inputImage->rawImageData[x]), 1, 1, data);

		if(scanCount != 1)
		{
			printf("ERROR: Bad Data formatting");

				freeImage(inputImage);

				return 13;
		}
	}
	
	//Initializing the rows of the 2D array to store the image data
	inputImage->imageData = (int**)malloc(inputImage->height * sizeof(int*));

	//For loop to initialize the columns of the array
	for(int x = 0; x < inputImage->height; x++)
	{
		inputImage->imageData[x] = (int*)malloc(inputImage->width * sizeof(int));
	}

	int rawDataCount = 0; //Variable for counting through the raw data list

	//For loop to put the captured raw data into imageData so that it can be used in asci routines
	for(int y = 0; y < inputImage->height; y++)
	{
		for(int b = 0; b < inputImage->width; b++)
		{	
			//Puts the raw image data into the appropriate place in the 2d array
			inputImage->imageData[y][b] = inputImage->rawImageData[rawDataCount];
			
			//Check that the current input is correct
			if(inputImage->imageData[y][b] < 0 ||
					inputImage->imageData[y][b] > 255)
			{
				printf("ERROR: Bad Data");

				freeImage(inputImage);

				return 8;
			}

			//Iterate rawDataCount
			rawDataCount++;
		}
	}


	return 0;
}
