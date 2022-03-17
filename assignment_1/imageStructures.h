//Contains the structures to store image files

//magicNumber = Magic number of the pgm file either P5 or P2
//magic_Numer = Raw version of the magic number
//commentLine = CommentLine indicated by #
//width, height = Dimensions of the pgm file
//maxGray = The maximum gray value of the pgm file
//imageData = 2d array to store the data of the pgm file
//rawImageData = 1d array to store the data of the pgm file
typedef struct
{
  char magicNumber[2];
  unsigned short *magic_Number;
  char *commentLine;
  unsigned int width, height;
  unsigned int maxGray;

  int **imageData;
  int *rawImageData;
} Image;
