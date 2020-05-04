/*
	Author DEMOURGUES LISE 
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "./built-in.c"

int main(int argc, char const *argv[]) {
	char **args;
	int proceed = 1;

	pid_t pid;
	int status;

	while(proceed) {

		printf("\033[0;36m%s\033[0m\033[0;35m%s\033[0m %%", getenv("USER"), getenv("PWD"));
		fflush(stdout);

		args = read_line();

		if (end_of_file(args)) {
			proceed = 0;
			printf("\n");
			//exit(-1);
		}

		if (!empty_line(args)) {

			pid = fork();
			//printf("%d\n", pid);
			if (pid == 0) { // if child process

				if (execvp(args[0], args) == -1) {
					perror("error while execvp");
					exit(EXIT_FAILURE);
				}
			}

			//printf("%d\n", pid);
			if (pid < 0) { // error while fork
				perror("error while fork");
			} else if (pid > 0) { 
				if (wait(&status) < 0) {
					perror("error while parent was waiting");
				}
			}
		}
	}

	free(args);
	return 0;
}