#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int f1(int x, int a, int c, int m ){
    long int x1 = x*a+c;
    return (int)(x1%m);
}
pthread_mutex_t mVar = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cVar = PTHREAD_COND_INITIALIZER;
int run = -1;
//make a struct to contain the arguments for the thread
struct thread_args{
    int x;
    int a;
    int c;
    int m;
    int points;
};
//Process for runner thread
/*
    Wait to receive a message from the main process 
 While message is not quit 
  Generate a number x_new by calling f1(x, a, c, m) 
  Send x_new back to the main process 
  Set x = x1new 
 Exit 

 Ignore points for now
*/
void *runner(void *param){
    
    struct thread_args *args = (struct thread_args *)param;
    int x = args->x;
    int a = args->a;
    int c = args->c;
    int m = args->m;
    int points = args->points;
    int x_new;
    while(run == -1){
        pthread_mutex_lock(&mVar);
        pthread_cond_wait(&cVar, &mVar);
        x_new = f1(x, a, c, m);
        printf("%d\n", x_new);
        args->x = x_new;
        pthread_mutex_unlock(&mVar);
    }

    pthread_exit(NULL);

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


    //close the file
    fclose(fp);

    //Create the threads. Each thread will be assigned a number from 0 to num_threads-1.
    pthread_t tid[num_threads];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    //Main process:
    //Create all of the threads
    //For reach round in loop:
    // 1.Message the threads to generate the next number
    // 2.Wait for all of the threads to finish in the numbers
    // 3.Print the number
    //Message the threads to quit
    //Wait for all of the threads to finish
    //Print the points
    

    //Create the threads
    for(int i = 0; i < num_threads; i++){
        pthread_create(&tid[i], &attr, runner, &args[i]);
    }
    //For each round
    for (int i = 1; i<num_rounds;i++ ){
        for (int j = 0;j<num_threads;j++){
            pthread_cond_signal(&cVar);
            run = 1;
            sleep(1);
            
            //printf("%d\n",args[i].x);
            
        }
        printf("\n");
    }

    //Wait for the threads to finish
    for(int i = 0; i < num_threads; i++){
        pthread_join(tid[i], NULL);
    }
    //Free the memory
    free(args);
    return 0;
}
   //end main