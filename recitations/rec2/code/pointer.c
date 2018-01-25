// Copyright (c) 2012 MIT License by 6.172 Staff

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char * argv[]) {  // What is the data type of argv?
  int i = 5;
  // pi stores the address of i. Note that & is the "address of" operator.
  int * pi = &i;
  int j = *pi;  // j now has value 5. * is the dereference operator.

  char c[] = "6.172";
  // array names are pointers to the first element
  // of the array (but see the ksplice gotcha above before doing arithmetic
  // on array pointers).
  char * pc = c;  // valid assignment casting an array to a pointer
  char d = *pc;  // d now has the value '6'.

  printf("char d = %c\n", d);

  // pointer to a char pointer
  // pcp stores the address of a char pointer
  char ** pcp;

  // Is the below assignment valid?
  pcp = argv;
  // Yes. argv is an array of char pointers and
  // argv points to the first element of the array.

  const char * pcc = c;  // pointer to character constant
  char const * pcc2 = c;  // what type is this?

  // Are the following assignments valid?
  *pcc = '7';  // No. Pointer is pointing to a char const
  pcc = *pcp;  // Yes. *pcp is a char pointer.
  pcc = argv[0];  // Yes. argv[0] is a char *.

  char * const cp = c;  // const pointer to character
  // Are the following assignments valid?
  cp = *pcp;  // invalid. cannot change the const pointer
  cp = *argv;  // invalid. cannot change the const pointer
  *cp = '!';  // valid. can modify the target of the pointer

  const char * const cpc = c;  // const pointer to char const.
  // Are the following assignments valid?
  cpc = *pcp;  // invalid
  cpc = argv[0];  // invalid
  *cpc = '@';  // invalid

  return 0;
}
