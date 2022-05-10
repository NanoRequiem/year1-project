#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"
#include "freeData.h"
#include "readFile.h"

#define SUCCESS_NO_ERRORS 0
#define FAIL_BAD_ARGS 1
#define FAIL_BAD_MAGIC_NUM 3
#define FAIL_BAD_COMMENT_LINE 4
#define FAIL_BAD_DIMENSIONS 5
#define FAIL_BAD_MAX_GRAY 6
#define FAIL_BAD_MALLOC 7
#define FAIL_BAD_DATA 8
#define FAIL_MISC 100

//Method to check the cmd line inputs
//
//requiredArguments - The arguments required for the utility
//argc - The actual number of arguments inputted by the user

int validateCmdArguments(int requiredArguments, int argc)
{
	if(requiredArguments != argc)
	{
		return FAIL_BAD_ARGS;
	}
	else
	{
		return SUCCESS_NO_ERRORS;
	}
}

//Method to initialize the image data
int initImage(Image *inputImage)
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

	return SUCCESS_NO_ERRORS;
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
		printf("ERROR: Bad Magic Number ");

		freeImage(inputImage);

		return FAIL_BAD_MAGIC_NUM;
	}

	//Used to scan for whitespace
	int scanCount = fscanf(data, " ");

	//Used to count through commentLine inputted
	int commentCount = 0;

	//Next char to check for a comment line. If it's there save it
	//If not put character back and continue
	char nextChar = getc(data);
	if(nextChar == '#')
	{
		//Initializing commentLine
		inputImage->commentLine = (char *) malloc(128);

		//Capturing input commentLine
		while(nextChar != '\n') {
			inputImage->commentLine[commentCount] = nextChar;

			nextChar = getc(data);

			commentCount++;

			if(commentCount > 128) {
				printf("ERROR: Bad Comment Line ");

				return FAIL_BAD_COMMENT_LINE;
			}
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
		printf("ERROR: Miscellaneous (Bad header data)");

		freeImage(inputImage);

		return FAIL_MISC;
	}

	//Validation checks for the width and heightvalues
	if(inputImage->width < 1 || inputImage->width >= 65536 ||
		inputImage->height < 1 || inputImage->height >= 65536)
	{
		printf("ERROR: Bad Dimensions ");

		freeImage(inputImage);

		return FAIL_BAD_DIMENSIONS;
	}

	//Validation check for maxGray value
	if(inputImage->maxGray != 255)
	{
		printf("ERROR: Bad Max Gray Value ");
		return FAIL_BAD_MAX_GRAY;
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

	//Check malloc occured
	if(inputImage->imageData == NULL)
	{
		printf("ERROR: Image Malloc Failed ");
		freeImage(inputImage);
		return FAIL_BAD_MALLOC;
	}

	//For loop to initialize the columns of the array
	for(int x = 0; x < inputImage->height; x++)
	{
		inputImage->imageData[x] = (int*)malloc(inputImage->width * sizeof(int));

		//Check malloc occured
		if(inputImage->imageData[x] == NULL)
		{
			printf("ERROR: Image Malloc Failed ");
			freeImage(inputImage);
			return FAIL_BAD_MALLOC;
		}
	}

	//values to index the 2D array
	int x = 0;
	int y = 0;
	//Value to count the amount read
	int countData = 0;

	//For loop that goes through all of the image's data and saves it
	//First for loop goes through the rows of the 2d array where as the
	//second for loop goes through the columns of the 2d array.
	while(fscanf(data, " %u",&(inputImage->imageData[x][y])) == 1)
	{
		countData++;
		//Validation check on the captured data
		if(inputImage->imageData[y][x] < 0 ||
				inputImage->imageData[y][x] > 255)
		{
			printf("ERROR: Bad Data ");

			freeImage(inputImage);

			return FAIL_BAD_DATA;
		}

		x++;
		//iterate over counter variables
		if(x == inputImage->width)
		{
			x = 0;
			y++;

			//ensure that a segmentation fault does not occur
			if(y == inputImage->height)
			{
				break;
			}
		}
	}

	int datacheck = 0;

	//Check that there is no remaining data in the file
	if(fscanf(data," %u", &datacheck) == 1)
	{
		printf("ERROR: Bad Data ");

		return FAIL_BAD_DATA;
	}

	//Check that enough data was read in compared to expected
	if(countData < inputImage->width * inputImage->height)
	{
		printf("ERROR: Bad Data ");

		return FAIL_BAD_DATA;
	}

	//Converts and stores current stored data as raw binary data
	int rawStatus = saveRAWData(inputImage);

	if(rawStatus != 0)
	{
		printf("ERROR: Miscellaneous (Bad Raw Data)");

		freeImage(inputImage);

		return FAIL_MISC;
	}

	return SUCCESS_NO_ERRORS;
}

int saveRAWData(Image *InputImage)
{
	//initialize rawImageData
	long nImageBytes = InputImage->width * InputImage->height * sizeof(int);
	InputImage->rawImageData = (int *) malloc(nImageBytes);

	if(InputImage->rawImageData == NULL)
	{
		printf("ERROR: Image Malloc Failed ");
		freeImage(InputImage);
		return FAIL_BAD_MALLOC;
	}

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

	return SUCCESS_NO_ERRORS;
}

int ReadRAWData(Image *inputImage, FILE *data)
{
	//Skips blank space line so that the data can be read
	fscanf(data, " ");

	//initialize rawImageData
	long nImageBytes = inputImage->width * inputImage->height * sizeof(int);
	inputImage->rawImageData = (int *) malloc(nImageBytes);

	if(inputImage->rawImageData == NULL)
	{
		printf("ERROR: Image Malloc Failed ");
		freeImage(inputImage);
		return FAIL_BAD_MALLOC;
	}

	//Count variable to check between expected amount of data read in and actual amount of data read in
	int countData = 0;
	int x = 0;

	while(fread(&(inputImage->rawImageData[x]), 1, 1, data) == 1)
	{
		x++;
		countData++;

		if(x >= inputImage->width * inputImage->height) {
			break;
		}
	}

	int datacheck = 0;

	//Check that there is no remaining data in the file
	if(fread(&datacheck, 1, 1, data) == 1)
	{
		printf("ERROR: Bad Data ");

		freeImage(inputImage);

		return FAIL_BAD_DATA;
	}

	//Check that enough data was read in compared to expected
	if(countData < inputImage->width * inputImage->height)
	{
		printf("ERROR: Bad Data ");

		freeImage(inputImage);

		return FAIL_BAD_DATA;
	}

	//Call function to convert rawData into ImageData
	if(rawDataToImageData(inputImage) != 0)
	{
		return FAIL_BAD_DATA;
	}

	return SUCCESS_NO_ERRORS;
}

int rawDataToImageData(Image *inputImage)
{
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
				printf("ERROR: Bad Data ");

				freeImage(inputImage);

				return FAIL_BAD_DATA;
			}

			//Iterate rawDataCount
			rawDataCount++;
		}
	}

	return SUCCESS_NO_ERRORS;
}
