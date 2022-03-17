
//Header file for the readFile.c program
//Brooklyn Mcswiney
//

//validateCmdArguments validates the command line arguments
//requiredArguments = Number of command line arguments needed
//argc = Number of command line arguments specified
int validateCmdArguments(int requiredArguments, int argc);

//Method to initialize the image struct
//inputImage = struct to save all the image data to
int initImage(Image *inputImage);

//method to read in the header data to the image struct
//inputImage = struct to save all the image data to
//data = file path to the opened image
int readImageHead(Image *inputImage, FILE *data);

//method to read in the values for the image should it be an ASCII file
//inputImage = struct to save all the image data to
//data = file path to the opened image
int readASCIIData(Image *inputImage, FILE *data);

//Method to convert the 2d list to a 1d list in case the ASCII data needs to be outputted as a raw image
//inputImage = struct to save all the image data to
int saveRAWData(Image *InputImage);

//Method to read in values for the image should it be a binary file
//inputImage = struct to save all the image data to
//data = file path to the opened image
int ReadRAWData(Image *inputImage, FILE *data);

//Method to convert the 1d list into a 2d list so that other modules can use the data
//inputImage = struct to save all the image data to
int rawDataToImageData(Image *inputImage);
