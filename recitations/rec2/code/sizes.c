// Copyright (c) 2012 MIT License by 6.172 Staff

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
  // Please print the sizes of the following types:
  // int, short, long, char, float, double, unsigned int, long long
  // uint8_t, int16_t, int32_t, and uint64_t

  // Here's how to show the size of one type. See if you can define a macro
  // to avoid copy pasting this code.

  printf("size of %s : %zu bytes \n", "int", sizeof(int));
  printf("size of %s : %zu bytes \n", "short", sizeof(short));
  printf("size of %s : %zu bytes \n", "long", sizeof(long));
  printf("size of %s : %zu bytes \n", "char", sizeof(char));
  printf("size of %s : %zu bytes \n", "float", sizeof(float));
  printf("size of %s : %zu bytes \n", "double", sizeof(double));
  printf("size of %s : %zu bytes \n", "unsigned int", sizeof(unsigned int));
  printf("size of %s : %zu bytes \n", "long long", sizeof(long long));
  printf("size of %s : %zu bytes \n", "uint8_t", sizeof(uint8_t));
  printf("size of %s : %zu bytes \n", "int16_t", sizeof(int16_t));
  printf("size of %s : %zu bytes \n", "int32_t", sizeof(int32_t));
  printf("size of %s : %zu bytes \n", "uint64_t", sizeof(uint64_t));



  // e.g. PRINT_SIZE("int", int);
  //      PRINT_SIZE("short", short);

  // Composite types have sizes too.
  typedef struct {
    int id;
    int year;
  } student;

  student you;
  you.id = 12345;
  you.year = 4;

  // You can just use your macro here instead: PRINT_SIZE("student", you);
  printf("size of student: %u Bytes \n", (unsigned int) sizeof(you));

  return 0;
}
