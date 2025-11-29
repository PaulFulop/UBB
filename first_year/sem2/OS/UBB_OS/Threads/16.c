#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct{
    int num;
    int* freq;
    pthread_mutex_t* mtx;
}data;

void* f(void* arg){
    data* d = (data*) arg;
    
    if(d->num == 0){
        pthread_mutex_lock(d->mtx);
        ++d->freq[0];
        pthread_mutex_unlock(d->mtx);
        return NULL;
    }

    while(d->num){
        pthread_mutex_lock(d->mtx);
        ++d->freq[d->num%10];
        pthread_mutex_unlock(d->mtx);

        d->num /= 10;
    }

    return NULL;
}

int main(int argc, char** argv){
    if(argc == 1){
        printf("No arguments.\n");
        exit(1);
    }

    int* arr = malloc(sizeof(int) * (argc-1));
    for(int i = 0; i < argc - 1; ++i){
        arr[i] = atoi(argv[i+1]);
        
        if(arr[i] == 0 && strcmp(argv[i+1], "0")){
            printf("Not all arguments are integers.\n");
            free(arr);
            exit(1);
        }
    }

    int *freq = malloc(sizeof(int) * 10);
    for(int i = 0; i < 10; ++i)
        freq[i] = 0;

    pthread_t* th = malloc(sizeof(pthread_t) * (argc-1));
    pthread_mutex_t mtx;
    pthread_mutex_init(&mtx, NULL);
    data* args = malloc(sizeof(data) * (argc-1));

    for(int i = 0; i < argc - 1; ++i){
        args[i].num = arr[i];
        args[i].freq = freq;
        args[i].mtx = &mtx;
        pthread_create(&th[i], NULL, f, (void*)&args[i]);
    }

    for(int i = 0; i < argc - 1; ++i)
        pthread_join(th[i], NULL);
    
    for(int i = 0; i < 10; ++i)
        printf("Digit %d appears %d times in total.\n", i, freq[i]);
    
    pthread_mutex_destroy(&mtx);
    free(freq);
    free(th);
    free(args);
    free(arr);
    return 0;
}
