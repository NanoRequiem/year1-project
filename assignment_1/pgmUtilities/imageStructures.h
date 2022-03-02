//Contains the structures to store image files

typedef struct
{
  unsigned char magicNumber[2];
  int width, height;
  int maxGray;

  int **imageData;
} Image;
