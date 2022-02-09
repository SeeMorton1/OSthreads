#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int f1(int x, int a, int c, int m ){
    long int x1 = x*a+c;
    return (int)(x1%m);
}

int main(int argc, char *argv[]){
    
    pthread_t tid;
    pthread_attr_t attr;
    printf("main: creating thread\n");
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&tid, &attr, f1, NULL);
    pthread_attr_destroy(&attr);
    printf("main: waiting for thread to finish\n");
    pthread_join(tid, NULL);
    printf("main: thread has finished\n");
    return 0;
}