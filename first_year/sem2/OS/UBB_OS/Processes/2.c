#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>

char *msg = NULL;

void handle(int sig){
    if (msg != NULL) {
        free(msg);
        msg = NULL;
    }

    wait(NULL);
}

int main(int argc, char* argv[]){
    
    if (argc != 3){
        printf("Provide two fifos!\n");
        exit(1);
    }

    int pid = fork();

    if (pid == 0) {
        int fd = open(argv[1], O_RDONLY);

        if (fd < 0){
            perror("Error opening fifo.\n");
            exit(1);
        }
        
        int len = 0;
        while (1){
            if (0 < read(fd, &len, sizeof(int))){
                char *recv = malloc((len + 1) * sizeof(char));
                int read_bytes = 0;

                while (read_bytes < len) {
                    int k = read(fd, recv, (len - read_bytes) * sizeof(char));

                    if (k > 0)
                        read_bytes += k;
                }

                recv[len] = 0;
                printf("%s", recv);
                free(recv);
            }
            else {
                exit(0);
            }
        }

        exit(0);
    }
    else if (pid > 0) {

        signal(SIGINT, handle);
        signal(SIGCHLD, handle);
        
        int fd = open(argv[2], O_WRONLY);
        if (fd < 0){
            perror("Error opening fifo.\n");
            exit(1);
        }

        msg = malloc(sizeof(char) * 256);
        memset(msg, 0, sizeof(char) * 256);
        
        while(1){
            fgets(msg, 256 * sizeof(char), stdin);
            int len = strlen(msg);
            
            write(fd, &len, sizeof(int));
            write(fd, msg, sizeof(char) * len);
            memset(msg, 0, sizeof(char) * 256);
        }

    }
    else {
        perror("Error creating process.\n");
        exit(1);
    }

    return 0;
}
