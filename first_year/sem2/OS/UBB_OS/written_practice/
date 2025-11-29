#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

void f(){
    char* str = malloc(256 * sizeof(char));
    printf("Are you sure you want to stop the program?\n> ");
    scanf("%s", str);
    
    if(strcmp(str, "yes") == 0){
        free(str);
        exit(0);
    }
    free(str);
}

int main(){
    
    signal(SIGINT, f);
    while(1){

    }

    return 0;
}
