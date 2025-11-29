#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int count = 1;
    while (count < argc) {
        int p[2];
        pipe(p);
        int child = fork();

        if (child < 0){
            perror("fork fail\n");
            exit(1);
        }
        else if (child == 0){
            char *args[]={argv[count], NULL};
            execvp(args[0], args);
            char text[200];
            close(p[0]);
            snprintf(text, sizeof(text), "Unable to run '%s': not a valid command", argv[count]);
            int size = strlen(text); 
            write(p[1], text, size);
            close(p[1]);
            ++count;
            exit(1);
        }
        else{
            close(p[1]);
            ++count;
            char buf[100] = {0};
            int cnt = read(p[0], &buf, sizeof(buf));

            if (cnt > 0)
                printf("%s. The child pid: %d.\n", buf, child);
            close(p[0]);
            wait(0);
        }
    }

    return 0;
}
