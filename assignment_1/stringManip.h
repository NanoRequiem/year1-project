
//Function to check that a given string follows
//the structure - "[filename]_<row>_<column>.pgm"
//inputString - File name to be checked for the correct template
int checkTemplate(char *inputString);

//function to run through the given template and output what
//the file name should be given coordinates
//OutputTemplate - The template for the name of the output with <row>_<column>
//outputName - Pointer to the actual name to be outputted
//x - X coordinate of the tile to be outputted
//y - y coordinate of the tile to be outputted
int getOutputName(char *outputTemplate, char *outputName, int x, int y);
