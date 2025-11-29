#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int p[2];
	if (-1 == pipe(p)) {
		perror("Error creating pipe!");
		exit(1);
	}

	int f = fork();

	if (-1 == f) {
		perror("Erorr on fork!");
		exit(1);
	}
	else if (0 == f) {
		FILE* cmd_out = popen("ps -ef | awk 'NR > 1 {print $5}'", "r");
		char* buf = malloc(101 * sizeof(char));
		fread(buf, 1, 100, cmd_out);

		int k = 0;
		while((k = fread(buf, 1, 100, cmd_out)) > 0) {
			//buf[k] = 0;
			write(p[1], &k, sizeof(int));
			write(p[1], buf, k);
			//printf("%s", buf);

		free(buf);
		pclose(cmd_out);
		close(p[1]);
		exit(0);
	}
	else {
		close(p[1]);
		char *buf = malloc(101 * sizeof(char));
		int k = -1;

		while (k != 0) {
			read(p[0], &k, sizeof(int));

			if (k > 0){
			  	read(p[0], buf, k);
                          	buf[k] = 0;
                          	printf("%s", buf);
			}
		}
		free(buf);
		close(p[0]);
		wait(NULL);
	}
	return 0;
}
