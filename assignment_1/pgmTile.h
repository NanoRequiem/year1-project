
//Header file for pgmTile file
//Brooklyn Mcswiney

//Main method to read in cmd line arguments
//argc = Number of command line arguments
//argv[1] = name of image file to be inputted
//argv[2] = name of image file to be outputted
int main(int argc, char **argv);

//Initializes the new image structure to store the tiled images
//inputImage - The image already stored to copy the header data from
//tileFactor - factor that the input image is being tiled to
//outImageName - Templat of the image to be outputted.
int newImageInit(Image *inputImage, int tileFactor, char *outImageName);

//Initializes the lists of data points for each tile
int initOutImageData(Image *outImage);

//Gets the data from the input image that is relevant to the current tile using the offsets
//XOffset - Off set for the data points in the x axis
//YOffset - Off set for the data points in the y axis
//inputImage - image input that needs to be looped through
//outImage - current image tile that needs to capture data
int getTileData(int XOffset, int YOffset, Image *inputImage, Image *outImage);
