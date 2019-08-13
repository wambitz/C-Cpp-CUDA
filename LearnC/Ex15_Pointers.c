#include <stdio.h>

int main(int argc, char const *argv[])
{
  // create two arrays we care about
  int ages[] = {23, 43, 12, 89, 2};
  char* names[] = { "Alan", "Frank", "Mary","Jhon", "Lisa"};
  
  // safely get the size of ages
  int count = sizeof(ages) / sizeof(int);
  int i = 0;

  // first way using indexin
  for (i = 0; i < count; i++)
  {
    printf("%s has %d years alive\n", names[i], ages[i]);
  }
  printf("---\n");

  // setup the pointers to start of the arrays
  int* cur_age = ages;

  /*************************************************************************** 
   * If you use only one pointer the program breaks, because when you move in
   * memory 1 byte, if you use a double pointer you are creating an array
   * of pointers which its elements are 4 or 8 bytes width, depending on the 
   * architecture. If you change the char** for int* it won't break. Because
   * for this code the memory movements are done each 4 bytes for integers.
   **************************************************************************/
  char** cur_name = names;

  // second way using pointers
  for (i = 0; i < count; i++)
  {
    // printf("%d is %d years old.\n",  cur_name+i, names+i); --> This print addresses
    printf("%s is %d years old.\n",  *(cur_name+i), *(cur_age+i));
  }
  printf("---\n");

  // third way, pointers are just arrays
   for (i = 0; i < count; i++)
   {
    printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
   }
   printf("---\n");

   // fouth way with pointers in a stupid complex way
   /*************************************************************
    * Here you assign to cur_name pointer the address of the first
    * element of the names array, this work in the same way for
    * for cur_age.
    * Then the for loop compares if the the substraction from 
    * the address of first element and the adrress stored in the
    * pointer are less than count(5), then result is in bytes.
    * At last increase the pointer to move to next address
    ************************************************************/

   for (cur_name = names, cur_age = ages; 
        (cur_age - ages) < count;
        cur_name++, cur_age++)
   {
      printf("%s lived %d years so far.\n", *cur_name, *cur_age);
      // printf("cur_name: %d, cur_age: %d, cur_age - ages: %d\n",
      //                           cur_name, cur_age, cur_age - ages);
   }
   printf("---\n");
   // printf("%d ages\n", *ages); // First element of the array
   // printf("%p ages\n", ages);  // First element address
 
  /********************************************************************
   * This code will break if you change the type of the pointer to the 
   * array. In other way you would have to use a double pointer so it
   * doesn't break.
   *******************************************************************/
  // int a[] = {1, 2};
  // int b[] = {3, 4};
  // int* c[] = {a, b};
  // int* ptr_to_a = c;
  // int* ptr_to_ptr_a = ptr_to_a;      // If you code char* you will have a memory corruption

  // for (i = 0; i < 4; i++)
  // {
  //   printf("a address: %d, a value: %d\n", ptr_to_a+i, *(ptr_to_a+i));
  //   // printf("%s is %d years old.\n", *(cur_name+i), *(cur_age+i));
  // }
  // printf("---\n");

  return 0;
}