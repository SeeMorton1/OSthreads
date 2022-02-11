#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int f1(int x, int a, int c, int m ){
    long int x1 = x*a+c;
    return (int)(x1%m);
}


int main(int argc, char *argv[]){
    //Read in the file from command line arguments
    FILE *fp = fopen(argv[1], "r");
    //Print the name of the file
    printf("%s\n", argv[1]);
    
    if(fp == NULL){
        printf("Error opening file\n");
        return 1;
    }
    //The first line of the file will contain two numbers: the number of threads to create, and the number of rounds to run.
    int num_threads, num_rounds;
    fscanf(fp, "%d %d", &num_threads, &num_rounds);
    //There will be a num_threads amount of lines after that containing four numbers: the starting value, the multiplier, the increment, and the modulus.
    //Read in the values from the file and store them
    int *values = malloc(num_threads * sizeof(int));
    int *a = malloc(num_threads * sizeof(int));
    int *c = malloc(num_threads * sizeof(int));
    int *m = malloc(num_threads * sizeof(int));
    for(int i = 0; i < num_threads; i++){
        fscanf(fp, "%d %d %d %d", &values[i], &a[i], &c[i], &m[i]);
    }
    printf("%d %d %d %d\n", values[0], a[0], c[0], m[0]);

    
    return 0;
}