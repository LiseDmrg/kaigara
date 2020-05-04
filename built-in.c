#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* split_assignation(char* str);

// list of built-in commands
char *built_in_command[] = {
	"cd",
	"help",
	"export",
	"exit",
	"echo"
};

/*
  Builtin commands implementation
*/

// cd command function
int my_cd(char** args) {

	if (args[1] == NULL) {
		printf("cd command expect argument\n");
	} else if (chdir(args[1]) != 0) {
		perror("error during chdir()");
	}
	return 1; 
}

// export command function
int my_export(char** args) {

	char* value = split_assignation(args[1]);
	if (setenv(args[1], value, 1) < 0) {
		perror("error while export");
	}
	return 1; 
}
/*
	split string VARIABLE=value in two strings by replacing '=' by '\0'
*/
char* split_assignation(char* str) {
	char* separator = str;
	while(*separator) {
		if (strncmp(separator,"=", sizeof(*separator)) == 0) {
			*separator = '\0';
			return separator+1;
		}
		separator++;
	}
	return NULL;
}

// help command function 
int my_help(char** args) {
	printf("This is a small shell program\nAuthor: Lise Demourgues\n");
	printf("I tried to implement built-in command, the followings are available:\n");

	for (int i = 0; i < (sizeof(built_in_command) / sizeof(char *)); i++) {
    	printf(" %s\n", built_in_command[i]);
  	}

	printf("for other programms use man or cmd --help\n");
	printf("To customise the prompt, set the env-variable called MYPROMPT\n");
	return 1;
}

// exit command function
int my_exit(char** args) {
	exit(-1);
}

//echo command function 
int my_echo(char** args) {
	for(int i = 1; i < (sizeof(args)-1); i++)
		printf("%s", args[i]);
	printf("\n");
	return 1; 
}

// list of built-in commands code

int (*built_in_command_body[]) (char **) = {
	&my_cd,
	&my_help,
	&my_export,
	&my_exit,
	&my_echo
};

/*
	test if its an internal command 
*/

int internal_cmd(char** args) {
	for (int i = 0; i < (sizeof(built_in_command) / sizeof(char *)); i++) {
    	if (strcmp(args[0], built_in_command[i]) == 0)
      		return (*built_in_command_body[i])(args);
  	}
  	return 0;
}
