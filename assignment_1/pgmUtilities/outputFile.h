//Header file for the outputFile program
//Program will output a file from what is saved within the
//image data structure.

int outputImage(Image *inputImage, char *outFile);

//Outputs the data of an ascii file
int writeASCIIData(Image *inputImage, FILE *outFile);

//Outputs the data of a binary file
int writeRAWData(Image *inputImage, FILE *outputFile);
