#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void* f(void* arg){
    char* str = (char*)arg;
    int n = strlen(str);
    for(int i = 0; i < n; ++i)
        if(isalpha(str[i])){
             if(isupper(str[i]))
                 str[i] = tolower(str[i]);
             else
                 str[i] =  toupper(str[i]);
    }
    return NULL;
}

int main(int argc, char** argv){
    if(argc == 1){
        printf("No arguments.\n");
        exit(1);
    }
   
    pthread_t* th = malloc(sizeof(pthread_t) * (argc-1));

    for(int i = 0; i < argc-1; ++i)
        pthread_create(&th[i], NULL, f, (void*)argv[i+1]);
    
    for(int i = 0; i < argc-1; ++i)
        pthread_join(th[i], NULL);

    for(int i = 1; i < argc; ++i)
        printf("%s ", argv[i]);
    printf("\n");
    free(th);
    return 0;
}
