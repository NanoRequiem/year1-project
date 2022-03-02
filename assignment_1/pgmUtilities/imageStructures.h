//Contains the structures to store image files
typedef struct _image
{
  char magic_number[2];
  int width, height;
  int maxGray;

  int **imageData[width][height];
}
