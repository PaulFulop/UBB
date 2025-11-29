#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char* str;
    int *countDigits, *countLetters, *countSpecial;
    pthread_mutex_t* mutexes;
}data;

void* f(void* arg){
    data* d = (data*) arg;
    int len = strlen(d->str);

    for(int i = 0; i < len; ++i){
        if(isdigit(d->str[i])){
            pthread_mutex_lock(&d->mutexes[0]);
            ++(*d->countDigits);
            pthread_mutex_unlock(&d->mutexes[0]);
        }
        else if (isalpha(d->str[i])){
            pthread_mutex_lock(&d->mutexes[1]);
            ++(*d->countLetters);
            pthread_mutex_unlock(&d->mutexes[1]);
        }
        else{
            pthread_mutex_lock(&d->mutexes[2]);
            ++(*d->countSpecial);
            pthread_mutex_unlock(&d->mutexes[2]);
        }
    }

    return NULL;
}

int main(int argc, char** argv){

    if (argc == 1){
        printf("No arguments.\n");
        exit(1);
    }
    
    pthread_mutex_t* mutexes = malloc(sizeof(pthread_mutex_t) * 3);
    for(int i = 0; i < 3; ++i)
        pthread_mutex_init(&mutexes[i], NULL);

    pthread_t* th = malloc(sizeof(pthread_t) * (argc-1));
    data* args = malloc(sizeof(data) * (argc-1));
    
    int totalDigits = 0, totalLetters = 0, totalSpecial = 0;
    for(int i = 0; i < argc-1; ++i){
        args[i].str = argv[i+1];
        args[i].countDigits = &totalDigits;
        args[i].countLetters = &totalLetters;
        args[i].countSpecial = &totalSpecial;
        args[i].mutexes = mutexes;
        pthread_create(&th[i], NULL, f, (void*)&args[i]);
    }

    for(int i = 0; i < argc-1; ++i)
        pthread_join(th[i], NULL);
    
    printf("We have %d digits, %d letters and %d special characters from the arguments.\n", totalDigits, totalLetters, totalSpecial);
    
     for(int i = 0; i < 3; ++i)
        pthread_mutex_destroy(&mutexes[i]);
    free(th);
    free(args);
    return 0;
}
