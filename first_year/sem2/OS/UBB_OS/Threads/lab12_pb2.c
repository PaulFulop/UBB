#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_cond_t cond_th1, cond_th2;
pthread_mutex_t mtx;
int arr[5];
int ready_for_check = 0;  // thread 1 sets to 1 after generating array
int ready_for_generate = 1;  // thread 2 sets to 1 after checking array
int sorted = 0;


void* GenerateArray(void* args) {
    while (1) {
        pthread_mutex_lock(&mtx);
        while (!ready_for_generate)
            pthread_cond_wait(&cond_th1, &mtx);

        if (sorted) {
            printf("Sorted!\nArray: ");
            for (int i = 0; i < 5; ++i)
                printf("%d ", arr[i]);
            printf("\n");

            pthread_mutex_unlock(&mtx);
            return NULL;
        } else {
            printf("Unsorted array: ");
            for (int i = 0; i < 5; ++i)
                printf("%d ", arr[i]);

            printf("\n");
            printf("Generating new array...\n");
            for(int i = 0; i < 5; ++i)
                arr[i] = rand() % 1001;
        }

        ready_for_check = 1;
        ready_for_generate = 0;
        pthread_cond_signal(&cond_th2);
        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

void* CheckSorted(void* args) {
    while (1) {
        pthread_mutex_lock(&mtx);
        while (!ready_for_check)
            pthread_cond_wait(&cond_th2, &mtx);

        printf("Checking array...\n\n");
        sorted = 1;
        for (int i = 1; i < 5; ++i) {
            if (arr[i] < arr[i - 1]) {
                sorted = 0;
                break;
            }
        }

        ready_for_generate = 1;
        ready_for_check = 0;

        pthread_cond_signal(&cond_th1);  // Always signal so generator continues
        pthread_mutex_unlock(&mtx);

        if (sorted)
            return NULL;
    }
    return NULL;
}

int main(int argc, char **argv){
    pthread_t th1, th2;
    pthread_create(&th1, NULL, GenerateArray, NULL);
    pthread_create(&th2, NULL, CheckSorted, NULL);
    pthread_cond_init(&cond_th1, NULL);
    pthread_cond_init(&cond_th2, NULL);
    pthread_mutex_init(&mtx, NULL);
    
    srand(time(NULL));
    
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_cond_destroy(&cond_th1);
    pthread_cond_destroy(&cond_th2);
    pthread_mutex_destroy(&mtx);
    return 0;
}
