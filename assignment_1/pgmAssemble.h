
//Header file for the pgma2b file
//
//Brooklyn Mcswiney

//Main method to read in cmd line arguments
//argc = Number of command line arguments
//argv[1] = output file name
//argv[2] = output width
//argv[3] = output height
//argv[3i + 1] = row at which sub image starts
//argv[3i + 2] = column at which sub image starts
//argv[3i + 3] = name of the sub image
int main(int argc, char **argv);

//Initialize the list of image structures
//ImageList - pointer to the list of images
//numbOfImage - number of images to be initialized 
int initImageList(Image **ImageList, int numbOfImage);
