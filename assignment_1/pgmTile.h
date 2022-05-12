
//Header file for pgmTile file
//Brooklyn Mcswiney

//Main method to read in cmd line arguments
//argc = Number of command line arguments
//argv[1] = name of image file to be inputted
//argv[2] = name of image file to be outputted
int main(int argc, char **argv);

int newImageInit(Image *inputImage, int tileFactor, char *outImageName);

int initOutImageData(Image *outImage);

int getTileData(int XOffset, int YOffset, Image *inputImage, Image *outImage);
