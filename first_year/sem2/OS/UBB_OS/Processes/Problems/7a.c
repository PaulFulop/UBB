#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char** argv){
    
    if (argc != 3){
        perror("Invalid number of arguments.\n");
        exit(1);
    }

    int f_read = open(argv[1], O_RDONLY);
    if (f_read < 0){
        perror("Error opening the fifo.\n");
        exit(1);
    }

    int f_write = open(argv[2], O_WRONLY);
    if (f_write < 0){
        perror("Error opening the fifo.\n");
        exit(1);
    }

    srandom(getpid());

    int num = 0, total;
    while (num != 10){
        int rand = random() % 10 + 1;
        write(f_write, &rand, sizeof(int));
        printf("Sent %d to the other process.\n", rand);

        total = 0;
        while(total < sizeof(int)){
            int read_bytes = read(f_read, (char*)&num + total, sizeof(int) - total);
            total += read_bytes;
        }
        printf("Read number %d from the other process.\n", num);
    }
    
    printf("Found number 10.\n");
    close(f_read);
    close(f_write);
    return 0;
}
