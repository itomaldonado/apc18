#include <stdio.h>
#include <stdlib.h>

// Get the number of inputs from the user
// Sum the inputs together.
int main(int argc, char* argv[]){
    if (argc < 2) {
        printf("Please pass at least one integer argument \n");
        return 1;
    }
    int z = atoi(argv[1]);
    int* n = (int*)malloc(sizeof(int)*z);
    int i;
    int sum = 0;
    for (i=0; i < z; i++) {
        printf("Please enter an integer : "); 
        scanf("%d", n++);
        printf("The integer entered was %d \n", n[i-1]);
        sum += n[i-1];
    }

    printf("Sum of all numbers is: %d\n", sum);
    
    return 0; 
} 