// Copyright (c) 2012 MIT License by 6.172 Staff

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define swap2(i, j) (i^=j^=i^=j)

void swap(int *i, int *j) {
  *i ^= *j;
  *j ^= *i;
  *i ^= *j;
}

int main() {
  int k = 1;
  int m = 2;
  swap(&k, &m);
  //swap2(k, m);
  // What would be the value of k and m printed below?
  printf("k = %d, m = %d\n", k, m);

  return 0;
}
