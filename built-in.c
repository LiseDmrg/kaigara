char* split_assignation(char* str);

// list of built-in commands
char *built_in_command[] = {
	"cd",
	"help",
	"export",
	"exit",
	"echo"
};

// list of built-in commands code

int (*built_in_command[]) (char **) = {
	&my_cd,
	&my_help,
	&my_export,
	&my_exit,
	&my_echo
};

// cd command function
void my_cd(char** args) {

	if (args[1] == NULL) {
		printf("cd command expect argument\n");
	} else if (chdir(args[1]) != 0) {
		perror("error during chdir()");
	}
}

// export command function
void my_export(char** args) {

	char* value = split_assignation(args[1]);
	if (setenv(args[1], value, 1) < 0) {
		perror("error while export");
	}
}
/*
	split string VARIABLE=value in two strings by replacing '=' by '\0'
*/
char* split_assignation(char* str) {
	char* separator = str;
	while(*separator) {
		if (*separator == "=") {
			*separator = '\0';
			return separator+1;
		}
		separator++;
	}
	return NULL;
}

// help command function 

void my_help() {
	printf("This is a small shell program\nAuthor: Lise Demourgues\n");
	printf("I tried to implement built-in command, the followings are available:\n");

	for (int i = 0; i < (sizeof(built_in_command) / sizeof(char *)); i++) {
    	printf(" %s\n", built_in_command[i]);
  	}

	printf("for other programms use man or cmd --help\n");
	printf("To customise the prompt, set the env-variable called MYPROMPT\n");
}