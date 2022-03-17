//Header file for the pgmComp program
//
//Brooklyn Mcswiney

//Main method to read in cmd line arguments
//argc = Number of command line arguments
//argv[1] = name of image file to be compared to the second image
//argv[2] = name of image file to be compared to the first image
int main(int argc, char **argv);

//Comp method to compare the saved data of each image inputted
//firstImage = Image struct that stores all the data for the first inputted image
//secondImage = Image struct that stores all the data for the second inputed image
int Comp(Image *firstImage, Image *secondImage);
