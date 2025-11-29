#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    int id, M;
    pthread_mutex_t* mutexes;
}data;

pthread_barrier_t b;

void* f(void* arg){
    data* d = (data*) arg;
    printf("Thread %d arrived at the start line.\n", d->id);
    pthread_barrier_wait(&b);

    for(int i = 0; i < d->M; ++i){
        pthread_mutex_lock(&d->mutexes[i]);
        printf("Thread %d has reached checkpoint %d.\n", d->id, i+1);
        usleep((rand()%101 + 100) * 1000);
        pthread_mutex_unlock(&d->mutexes[i]);
    }

    printf("Thread %d has finished the race!\n", d->id);
    return NULL;
}

int main(int argc, char** argv){

    if(argc != 3){
        printf("Invalid number of arguments.\n");
        exit(1);
    }

    int N = atoi(argv[1]), M = atoi(argv[2]);

    if (!N || !M){
        printf("Not all arguments are valid integers.\n");
        exit(1);
    }

    srand(getpid());

    pthread_mutex_t* mutexes = malloc(sizeof(pthread_mutex_t) * M);
    for(int i = 0; i < M; ++i)
        pthread_mutex_init(&mutexes[i], NULL);
    pthread_barrier_init(&b, NULL, N);
    
    pthread_t* th = malloc(sizeof(pthread_t) * N);
    data* args = malloc(sizeof(data) * N);
    for(int i = 0; i < N; ++i){
        args[i].M = M;
        args[i].id = i + 1;
        args[i].mutexes = mutexes;
        pthread_create(&th[i], NULL, f, (void*)&args[i]);
    }
    
    for(int i = 0; i < N; ++i)
        pthread_join(th[i], NULL);

    printf("\nThe thread race has finished.\n");
    
    for(int i = 0; i < M; ++i)
        pthread_mutex_destroy(&mutexes[i]);
    pthread_barrier_destroy(&b);
    free(args);
    free(mutexes);
    free(th);
    return 0;
}
