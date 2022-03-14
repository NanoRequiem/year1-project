#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imageStructures.h"

//Function to output the file to a binary file
int outputBinary(Image *inputImage, char *outFile) {

    //Opening file using user supplied name
    FILE *outputFile = fopen(outFile, "w");

    //Check that the output has been opened and is available
    if(outputFile == NULL) {
        printf("ERROR: Output File Path Not Found");
        return 11;
    }

    //Writing magic number, comment line, max gray, height and width values
    //to the new file
    //if statement to check that the comment line is present and output it if it's
    //present
    if(inputImage->commentLine == NULL)
    {
        fprintf(outputFile, "P5\n\n%d %d\n%d\n",
                                inputImage->width,
                                inputImage->height,
                                inputImage->maxGray);
    }
    else
    {
        fprintf(outputFile, "P5\n%s\n\n%d %d\n%d",
                                inputImage->commentLine,
                                inputImage->width,
                                inputImage->height,
                                inputImage->maxGray);
    }

    //Creating a new 1D list to store data to be outputted
    int *outputData = (int *)malloc(inputImage->width * inputImage->height *sizeof(int *));
    int outputDataCount = 0; //int value to count through output data and capture data

    //Loop through list and output data to the file
    for(int y=0; y<inputImage->height; y++) {
        for(int x=0; x<inputImage->width; x++) {
            printf("%d\n", inputImage->imageData[y][x]);
            outputData[outputDataCount] = inputImage->imageData[y][x];
        }
    }

    //Outputs data to the file
    fwrite(&outputData, sizeof(outputData), 4, outputFile);

    //Successful write so return 0
    return 0;
}