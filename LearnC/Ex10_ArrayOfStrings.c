#include <stdio.h>

int main(int argc, char const *argv[])
{
  int i = 0;
  int j = 0;

  
  // argv[3] = "hello"; // overwrite element value
  
  // go through each string in argv
  // why am I skipping arvv[0]
  for (i = 1; i < argc; i++)
  {
    printf("arg %d: %s\n", i, argv[i]);
  }

  // Let's make our own array of strings
  char *states[] = 
  {
      "California",
      "Oregon",
      "Washington",
      "Texas"
  };  

  // states[1] = argv[2];
  int num_states = 4;
  for (i = 0; i < num_states; i++)
  {
    printf("state %d: %s\n", i, states[i]);
  }

  // Two dimentions array, array of strings
  char numbers[4][10] =
  {
    {"One"},
    {"Two"},
    {"Three"},
    //{"Four"}
    NULL
  };

  // Print each element of the array, each character
  // for (i = 0; i < 4; i++)
  // {
  //   for (j = 0; j < 10; j++)
  //   {
  //     printf("number %d: %c\n", i, numbers[i][j]);
  //   }
  // }
  
  for (i = 0; i < 4; i ++)
  {
    printf("number %d: %s\n", i, numbers[i]);
  }


  return 0;
}