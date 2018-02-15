#include <stdio.h>
#include <stdlib.h>
int* my_malloc(int size , int set) {
  int* array = malloc(size * sizeof(int));
  int i;
  for (i = 0; i < size; i++) {
    *(array ++) = set;
  }
  return array;
}
void print_array(int* array , int size) {
  int i;
  for (i = 0; i < size; i++) {
    printf("Element %d = %d\n", i, array[i]);
  }
}

int main(int argc , char* argv []) {
  int* array = my_malloc (100, 3);
  print_array(array , 100);
  free(array);
}