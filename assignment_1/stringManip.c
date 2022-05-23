#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "stringManip.h"

int checkTemplate(char *inputString)
{
  char *contain;

  //Check if the template given is correct
  contain = strstr(inputString, "_<row>_<column>");

  //if(access(argv[3], W_OK) != 0) {
  //  printf("ERROR: Output Failed ");

  //  return FAIL_BAD_OUTPUT;
  //}

  //Output correct message depending on if the template is correct
  if(contain)
  {
    return 0;
  }
  else
  {
    printf("ERROR: Miscellaneous (Incorrect output file template)");

    return 100;
  }
}


int getOutputName(char *outputTemplate, char *outputName, int x, int y)
{
  //Initialize values to hold string versions of x and y
  char *outX = (char *)malloc(10 * sizeof(char));

  //Capture X and Y as a string
  sprintf(outX, "%d_%d.pgm", x, y);

  //add X and Y to the Template with the .pgm file ending
  for(int z = 0; z < strlen(outputTemplate); z++)
  {
    if(outputTemplate[z] == '<')
    {
      break;
    }
    else
    {
      outputName[z] = outputTemplate[z];
    }
  }

  strcat(outputName, outX);

  return 0;
}
