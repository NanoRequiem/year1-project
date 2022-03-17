//Header file for the outputFile program
//Program will output a file from what is saved within the
//image data structure.

//Method to open the output and write the header data to it
//inputImage = struct that stores data for the image to be outputted
//outFile = File path of the image to be outputted
int outputImage(Image *inputImage, char *outFile);

//Outputs the data of an ascii file
//inputImage = struct that stores data for the image to be outputted
//outFile = File path of the image to be outputted
int writeASCIIData(Image *inputImage, FILE *outFile);

//Outputs the data of a binary file
//inputImage = struct that stores data for the image to be outputted
//outFile = File path of the image to be outputted
int writeRAWData(Image *inputImage, FILE *outputFile);
