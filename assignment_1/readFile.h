
//Header file for the readFile.c program
//
//validateCmdArguments validates the command line arguments
int validateCmdArguments(int requiredArguments, int argc);

int initImage(Image *inputImage);

int readImageHead(Image *inputImage, FILE *data);
int readASCIIData(Image *inputImage, FILE *data);
int saveRAWData(Image *InputImage);
int ReadRAWData(Image *inputImage, FILE *data);
int rawDataToImageData(Image *inputImage);

int freeData(Image *inputImage);
