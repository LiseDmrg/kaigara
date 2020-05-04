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

#define LBUF 1024
#define LLIGNE 256
static char buf[LBUF];
static char* ligne[LLIGNE];

char** read_line();

int main(int argc, char const *argv[]) {
	char **args;
	int proceed = 1;

	pid_t pid;
	int status;

	while(proceed) {

		if (getenv("MYPROMPT") == NULL)
			printf("\033[0;36m%s\033[0m\033[0;35m%s\033[0m %%", getenv("USER"), getenv("PWD"));
		else
			printf("\033[0;36m%s\033[0m %%", getenv("MYPROMPT"));
		fflush(stdout);

		args = read_line();

		if (args == NULL) {
			proceed = 0;
			printf("\n");
			//exit(-1);
		}

		if (!(args[0] == NULL)) {

			if (internal_cmd(args) == 0) {

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
	}

	free(args);
	return 0;
}

char** read_line() { //written by our professor, will implement later
    int i = 0;
    int s;

    do {
        s = read(0, buf+i, 1);
        i += s;
    } while (i < LBUF-1  &&  s > 0  &&  buf[i-1] != '\n');

    if (s < 0) 
        perror("erreur de lecture dans lis_ligne");
    if (i == 0) 
        return NULL;

    // cut with space
    char* tok;
    buf[i] = '\0';
    i = 0;
    ligne[0] = strtok_r(buf, " \t\n\r", &tok);
    while (ligne[i] && i < LLIGNE-1) {
        i += 1;
        ligne[i] = strtok_r(NULL, " \t\n\r", &tok);
    }
    if (i == LLIGNE-2) 
    	ligne[LLIGNE-1] = NULL;
    return ligne;
}