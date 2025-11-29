#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int f = fork();
	if (-1 == f) {
		perror("Error creating pipe!");
		exit(1);
	}

	if (-1 == f) {
		perror("Erorr on fork!");
		exit(1);
	}
	else if (0 == f) {
		int w_fifo = open("./fifo", O_WRONLY);
		FILE* cmd_out = popen("ps -ef | awk 'NR > 1 {print $5}'", "r");
		char* buf = malloc(101 * sizeof(char));
		fread(buf, 1, 100, cmd_out);

		int k = 0;
		while((k = fread(buf, 1, 100, cmd_out)) > 0) {
			//buf[k] = 0;
			write(w_fifo, &k, sizeof(int));
			write(w_fifo, buf, k);
			//printf("%s", buf);
		}
		
		free(buf);
		pclose(cmd_out);
		close(w_fifo);
		exit(0);
	}
	else {
		int r_fifo = open("./fifo", O_RDONLY);
		close(r_fifo);
		char *buf = malloc(101 * sizeof(char));
		int k = -1;

		while (k != 0) {
			read(r_fifo, &k, sizeof(int));

			if (k > 0){
			  	read(r_fifo, buf, k);
                          	buf[k] = 0;
                          	printf("%s", buf);
			}
		}
		free(buf);
		close(r_fifo);
		wait(NULL);
	}
	return 0;
}
