#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n;
    printf("Insert the number of children here: ");
    scanf("%d", &n);

    pid_t* child_pids = malloc(n * sizeof(pid_t));
    if (child_pids == NULL) {
        perror("malloc failed");
        exit(1);
    }

    printf("\nParent pid: %d\n", getpid());

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Error on fork");
            exit(1);
        }

        if (pid == 0) {
            // In child process
            printf("Child pid: %d, Parent pid: %d\n", getpid(), getppid());
            exit(0);
        } else {
            // In parent process, store child PID
            child_pids[i] = pid;
        }
    }

    // Parent waits for all children
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Children pids: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", child_pids[i]);
    }
    printf("\n");

    free(child_pids);
    return 0;
}
