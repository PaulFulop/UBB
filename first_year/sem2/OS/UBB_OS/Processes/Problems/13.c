/*

   Using PIPE channels create and implement the following scenario:
   Process A reads N integer numbers from the keyboard and sends them to another process named B.
   Process B will add a random number, between 2 and 5, to each received number from process A and will send them to another process named C.
   Process C will add all the received numbers and will send the result back to process A. All processes will print a debug message before sending and after receiving a number.

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[]){
    int a2b[2], b2c[2], a2c[2];
    pipe(a2b); pipe(b2c); pipe(a2c);
    
    int f1 = fork();

    if (f1 < 0){
        perror("Error on fork.\n");
        exit(1);
    }
    else if(f1 > 0){
        int n, x;
        close(a2b[0]);
        scanf("%d", &n);
        write(a2b[1], &n, sizeof(int));
        for(int i = 0; i < n; ++i){
            scanf("%d", &x);
            printf("Sending number %d to process B...\n", x);
            write(a2b[1], &x, sizeof(int));
        }
        close(a2b[1]);
        wait(0);
    }
    else{
        close(a2b[1]);
        close(a2c[0]);
        close(b2c[0]);
        close(a2c[1]);
        srandom(time(NULL));
        
        int total = 0, n;
        while(total < sizeof(int)){
            int read_bytes = read(a2b[0], &n + total, sizeof(int) - total);
            total += read_bytes;
        }
        
        write(b2c[1], &n, sizeof(int));

        for (int i = 0; i < n; ++i){
            total = 0;
            int num;
            
            while(total < sizeof(int)){
                int read_bytes = read(a2b[0], &num + total, sizeof(int) - total);
                total += read_bytes;
            }
            
            printf("Receiving number %d from proces A...\n", num);
            int num1 = num;
            num += random() % 4 + 2;
            printf("Sending number %d + %d = %d to process C...\n", num1, num - num1, num);
            write(b2c[1], &num, sizeof(int));

        }

        close(a2b[0]);
        close(b2c[1]);
        exit(0);
    }
    
    int f2 = fork();

    if (f2 < 0){
        perror("Error on fork.\n");
        exit(1);
    }
    else if (f2 > 0){
        wait(0);
        close(a2c[1]);
        int total = 0, sum;

        while(total < sizeof(int)){
            int read_bytes = read(a2c[0], &sum + total, sizeof(int) - total);
            total += read_bytes;
        }
        
        printf("Receiving the number %d from process C...\n", sum);
        close(a2c[0]);
        printf("The final sum is %d.\n", sum);
    }
    else{
        close(a2c[0]);
        close(b2c[1]);
        close(a2b[0]);
        close(a2b[1]);

        int sum = 0;
        int n, total = 0;
        while(total < sizeof(int)){
            int read_bytes = read(b2c[0], &n + total, sizeof(int) - total);
            total += read_bytes;
        }

        for (int i = 0; i < n; ++i){
            total = 0;
            int num;
            while(total < sizeof(int)){
                int read_bytes = read(b2c[0], &num + total, sizeof(int) - total);
                total += read_bytes;
            }

            printf("Receiving number %d from process B...\n", num);

            sum += num;
        }
        
        printf("Sending number %d to process A...\n", sum);
        write(a2c[1], &sum, sizeof(int));
        close(b2c[0]);
        close(a2c[1]);
        exit(0);
    }

    close(b2c[0]);
    close(b2c[1]);
    printf("All pipes are closed correctly, and the whole program ended.\n");

    return 0;
}
