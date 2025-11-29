#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mtx;
char buffer[20];

typedef struct{
    FILE *fd1, *fd2;
} data;

void *f(void* arg){
    data *d = (data*) arg;
    
    while(1){
        pthread_mutex_lock(&mtx);
        
        int len = fread(buffer, 1, 20, d->fd1);
        if(len){
            buffer[len] = '\0';
            fwrite(buffer, 1, len, d->fd2);
        }
        else{
            break;
        }
        
        pthread_mutex_unlock(&mtx);
    }

    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main(int argc, char** argv){
    
    if (argc != 4){
        printf("Invalid number of arguments.\n");
        exit(1);
    }
    
    FILE* fd1 = fopen(argv[1], "r");
    FILE* fd2 = fopen(argv[2], "w");

    if(fd1 == NULL || fd2 == NULL){
        printf("Invalid files.\n");
        exit(1);
    }

    int n = atoi(argv[3]);

    if(!n){
        printf("Invalid number of threads.\n");
        exit(1);
    }
    
    pthread_t* th = malloc(sizeof(pthread_t) * n);
    data* args = malloc(sizeof(data) * n);
    pthread_mutex_init(&mtx, NULL);
    
    for(int i = 0; i < n; ++i){
        args[i].fd1 = fd1;
        args[i].fd2 = fd2;

        pthread_create(&th[i], NULL, f, (void*) &args[i]);
    }

    for(int i = 0; i < n; ++i)
        pthread_join(th[i], NULL);

    printf("Wrote to the file.\n");

    pthread_mutex_destroy(&mtx);
    free(th);
    free(args);
    fclose(fd1);
    fclose(fd2);
    return 0;
}
