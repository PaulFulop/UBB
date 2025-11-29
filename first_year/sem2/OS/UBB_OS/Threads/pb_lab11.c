#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct arg_t {
    int *potato;
    int id;
    pthread_mutex_t* mtx; 
};

void* f(void* a) {
    struct arg_t* x = (struct arg_t*)a;
    srand(time(NULL));
    
    while(1){
        pthread_mutex_lock(x->mtx);

        if (*(x->potato) < 0){
            pthread_mutex_unlock(x->mtx);
            break;
        }

        int r_sub = rand() % 91 + 10;
        *x->potato -= r_sub;
        
        int r_sleep_time = rand() % 201 + 100;
        usleep(r_sleep_time * 100);

        if (*(x->potato) < 0) {
            printf("Thread with id %d was first to make the potato negative.\n", x->id);
            pthread_mutex_unlock(x->mtx);
            break;
        }    

        pthread_mutex_unlock(x->mtx);
    }

    return NULL;
}

int main(int argc, char** argv){

    if (argc != 2){
        printf("Invalid number of arguments.\n");
        exit(1);
    }
    
    char* input = malloc(256 * sizeof(char));
    strcpy(input, argv[1]);

    int num = atoi(input);    
    if (num == 0){
        printf("Invalid argument.\n");
        exit(1);
    }
    
    srand(time(NULL));
    int potato = rand() % 9001 + 1000;
    
    pthread_t t[num];
    pthread_mutex_t mtx;
    pthread_mutex_init(&mtx, NULL);
    struct arg_t* arguments = malloc(sizeof(struct arg_t) * num);

    for (int i = 0; i < num; ++i){
        arguments[i].potato = &potato;
        arguments[i].id = i + 1;
        arguments[i].mtx = &mtx; 
        pthread_create(&t[i], NULL, f, &arguments[i]);
    }

    for (int i = 0; i < num; ++i)
        pthread_join(t[i], NULL);

    pthread_mutex_destroy(&mtx);
    free(input);
    free(arguments);
    return 0;
}
