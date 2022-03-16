//Header file for pgmReduce

//Main method for reading in cmd line arguments and calling read in and output modules
//
//argc = number of command line arguments
//**argv = list of all command line arguments
int main(int argc, char **argv)

//initReduced method for initializing the reduced file
//
//inputImage = image inputted
//reduced = Reduced image
int initReduced(Image *inputImage, Image *reduce);

//reduce method to actually reduce the image
//
//inputImage = image inputted
//reduced = Reduced image
//factor = The factor that input image is reduced by
int reduce(Image *inputImage, Image *reduced, int factor);