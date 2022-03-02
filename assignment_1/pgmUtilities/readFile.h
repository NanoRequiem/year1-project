
//Header file for the readFile.c program
//
//validateCmdArguments validates the command line arguments
int validatecmdArguments(int requiredArguments, int argc);

int initImage(Image *inputImage, FILE *data);

int ReadImageHead(Image *inputImage, FILE *data);
