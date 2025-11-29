#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

FILE* fd = NULL;
unsigned int  lines, words, chars;
pthread_mutex_t  mtx, line_mtx, word_mtx, char_mtx;

void* f(void* a){
    if (!fd) return NULL;

    while(1){
        char* line = NULL;
        size_t size = 0;
        pthread_mutex_lock(&mtx);
        int len =  getline(&line, &size, fd);

        if (len < 0){
            pthread_mutex_unlock(&mtx);
            free(line);
            return NULL;
        }
        pthread_mutex_unlock(&mtx);

        char *token = strtok(line, " ");
        while(token != NULL){
            pthread_mutex_lock(&word_mtx);
            ++words;
            pthread_mutex_unlock(&word_mtx);
            token = strtok(NULL, " ");
        }
        
        pthread_mutex_lock(&line_mtx);
        ++lines;
        pthread_mutex_unlock(&line_mtx);
        
        pthread_mutex_lock(&char_mtx);
        chars += strlen(line);
        pthread_mutex_unlock(&char_mtx);

        free(line);
    }
    return NULL;
}

int main(int argc, char **argv){
    if (argc != 3){
        printf("Invalid number of arguments.\n");
        exit(1);
    }

    char* filename = malloc(sizeof(char)* 256);
    char *num_str = malloc(sizeof(char)*100);
    strcpy(filename, argv[1]);
    strcpy(num_str, argv[2]);
    fd = fopen(filename, "r");

    if (fd == NULL){
        printf("Error opening the file!\n");
        exit(1);
    }
    int num = atoi(num_str);

    if (num == 0){
        printf("Invalid number!\n");
        exit(1);
    }
    
    pthread_t* th = malloc(sizeof(pthread_t) * num);
    pthread_mutex_init(&mtx, NULL);
    pthread_mutex_init(&line_mtx, NULL);
    pthread_mutex_init(&word_mtx, NULL);
    pthread_mutex_init(&char_mtx, NULL);

    for(int i = 0; i < num; ++i){
        pthread_create(&th[i], NULL, f, NULL);
    }

    for (int i = 0; i < num; ++i)
        pthread_join(th[i], NULL);

    
    printf("The total number of lines is: %d\nThe total number of words is: %d\nThe total number of characters is: %d\n", lines, words, chars);

    pthread_mutex_destroy(&mtx);
    pthread_mutex_destroy(&line_mtx);
    pthread_mutex_destroy(&word_mtx);
    pthread_mutex_destroy(&char_mtx);
    free(th);
    free(filename);
    free(num_str);
    fclose(fd);
    return 0;
}
