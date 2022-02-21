#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int f1(int x, int a, int c, int m ){
    long int x1 = x*a+c;
    return (int)(x1%m);
}

//make a struct to contain the arguments for the thread
struct thread_args{
    int x;
    int a;
    int c;
    int m;
    int points;
};
void *runner(void *param){
    struct thread_args *args = (struct thread_args *)param;
    int x = args->x;
    int a = args->a;
    int c = args->c;
    int m = args->m;
    int points = args->points;
    int i;
    for(i=0;i<points;i++){
        x = f1(x,a,c,m);
    }
    printf("%d\n",x);
    //exit
    pthread_exit(0);
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
    //There will be a num_threads amount of lines after that containing four numbers: a, c, m, and the initial value of x.
    //X is the starting value, a is the multiplier, c is the increment, and m is the modulus.
    //Read in the values from the file and store them in an array of structs

    struct thread_args *args = malloc(sizeof(struct thread_args) * num_threads);
    for(int i = 0; i < num_threads; i++){
        fscanf(fp, "%d %d %d %d", &args[i].a, &args[i].c, &args[i].m, &args[i].x);
        args[i].points = 0;
    }
    for (int i = 0; i< num_threads;i++){
        printf("%d %d %d %d %d\n", args[i].a, args[i].c, args[i].m, args[i].x, args[i].points);
    }

    //close the file
    fclose(fp);

    //Create the threads. Each thread will be assigned a number from 0 to num_threads-1.
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    //The arguments for each thread will be the array of structs thread_args
    

    //For each round:
    //1. Message the threads to generate the next number based on f1.
    //2. Wait for all threads to send in the numbers
    //3. Score the round
    //4. Print the round score




    //Free the memory
    printf("DOne");
    
    return 0;
}