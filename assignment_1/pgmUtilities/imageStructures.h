//Contains the structures to store image files

typedef struct
{
  char *magic_number[2];
  int width, height;
  int maxGray;

  int **imageData;
} Image;
