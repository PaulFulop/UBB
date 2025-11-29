#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct{
    int *arr, *arr1, *arr2;
    int id, step, n1, n2, M;
    int *k1, *k2;
    pthread_mutex_t* mtx;
}data;

void* f(void* arg){

    data* d = (data*)arg;

    for(int i = d->id; i < d->M; i += d->step){
        pthread_mutex_lock(d->mtx);
        if(d->arr[i] > 0){
            d->arr1[*d->k1] = d->arr[i];
            *d->k1 += 1;
        }

        if(d->arr[i] < 0){
            d->arr2[*d->k2] = d->arr[i];
            *d->k2 += 1;
        }
        pthread_mutex_unlock(d->mtx);
    }


    return NULL;
}

int main(int argc, char** argv){

    if(argc != 3)
    {
        printf("Invalid number of arguments.\n");
        exit(1);
    }

    int M = atoi(argv[1]), N = atoi(argv[2]);

    if (M == 0 || N == 0){
        printf("Not all arguments are integers.\n");
        exit(1);
    }

    srand(getpid());

    int n1 = 0, n2 = 0;
    int* arr = malloc(sizeof(int) * M);
    for(int i = 0; i < M; ++i){
        arr[i] = -5000 + (rand() % 10001);

        if(arr[i] < 0)
            ++n2;
        if(arr[i] > 0)
            ++n1;
    }

    printf("Original array:\n");
    for(int i = 0; i < M; ++i)
        printf("%d ", arr[i]);
    printf("\n\n");

    pthread_t* th = malloc(sizeof(pthread_t) * N);
    data* args = malloc(sizeof(data) * N);
    pthread_mutex_t mtx;
    pthread_mutex_init(&mtx, NULL);

    int k1 = 0, k2 = 0;
    int* arr2 = malloc(sizeof(int) * n1); //positive
    int* arr3 = malloc(sizeof(int) * n2); // negative
    for(int i = 0; i < N; ++i){
        args[i].arr = arr;
        args[i].arr1 = arr2;
        args[i].arr2 = arr3;
        args[i].mtx = &mtx;
        args[i].n1 = n1;
        args[i].n2 = n2;
        args[i].k1 = &k1;
        args[i].k2 = &k2;
        args[i].step = N;
        args[i].id = i;
        args[i].M = M;

        pthread_create(&th[i], NULL, f, (void*)&args[i]);
    }

    for(int i = 0; i < N; ++i)
        pthread_join(th[i], NULL);

    printf("Array of positive numbers:\n");
    for(int i = 0; i < n1; ++i)
        printf("%d ", arr2[i]);
    printf("\n\n");

    printf("Array of negative numbers:\n");
    for(int i = 0; i < n2; ++i)
        printf("%d ", arr3[i]);
    printf("\n");

    free(arr);
    free(arr2);
    free(arr3);
    free(th);
    free(args);
    pthread_mutex_destroy(&mtx);
    return 0;
}
