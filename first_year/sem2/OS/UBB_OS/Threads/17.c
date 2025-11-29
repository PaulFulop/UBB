#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    int *arr, *k, *flag;
    int N;
    pthread_mutex_t* mtx;
    pthread_cond_t *cond_even, *cond_odd;
}data;

void* GenerateEven(void* arg){
    data* d = (data*) arg;
    while(1){
        pthread_mutex_lock(d->mtx);
        while(*d->flag == 0)
            pthread_cond_wait(d->cond_even, d->mtx);

        int newNum = 1;
        while(newNum%2 == 1){
            newNum = rand() % 1000;
        }

        d->arr[*d->k] = newNum;

        ++(*d->k);
        *d->flag = 0;
        pthread_cond_signal(d->cond_odd);

        if(*d->k >= d->N){
            break;
        }

        pthread_mutex_unlock(d->mtx);
    }

    pthread_mutex_unlock(d->mtx);
    return NULL;
}

void* GenerateOdd(void* arg){
    data* d = (data*) arg;
    while(1){
        pthread_mutex_lock(d->mtx);
        while(*d->flag != 0)
            pthread_cond_wait(d->cond_odd, d->mtx);

        int newNum = 2;
        while(newNum%2 == 0){
            newNum = rand() % 1000;
        }
        
        d->arr[*d->k] = newNum;

        ++(*d->k);
        *d->flag = 1;
        pthread_cond_signal(d->cond_even);

        if(*d->k >= d->N){
            break;
        }

        pthread_mutex_unlock(d->mtx);
    }

    pthread_mutex_unlock(d->mtx);
    return NULL;
}

int main(){
    int N = -1;
    printf("Read the number: ");
    scanf("%d", &N);
    
    if(N < 0){
        printf("Invalid number.\n");
        exit(1);
    }
    
    srand(getpid());
    int* arr = malloc(sizeof(int) * N);
    pthread_t thEven, thOdd;
    
    pthread_mutex_t mtx;
    pthread_mutex_init(&mtx, NULL);

    pthread_cond_t cond_even, cond_odd;
    pthread_cond_init(&cond_even, NULL);
    pthread_cond_init(&cond_odd, NULL);

    int k = 0, flag = 1;
    data args;
    args.arr = arr;
    args.k = &k;
    args.N = N;
    args.flag = &flag;
    args.mtx = &mtx; 
    args.cond_even = &cond_even;
    args.cond_odd = &cond_odd;

    pthread_create(&thEven, NULL, GenerateEven, (void*)&args);
    pthread_create(&thOdd, NULL, GenerateOdd, (void*)&args);
    
    pthread_join(thEven, NULL);
    pthread_join(thOdd, NULL);
    
    printf("The array is: ");
    for(int i = 0; i < N; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond_even);
    pthread_cond_destroy(&cond_odd);
    free(arr);
    return 0;
}
