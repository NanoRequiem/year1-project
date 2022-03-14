//Contains the structures to store image files

typedef struct
{
  unsigned char magicNumber[2];
  unsigned short *magic_Number;
  char *commentLine;
  unsigned int width, height;
  unsigned int maxGray;

  unsigned int **imageData;
} Image;
