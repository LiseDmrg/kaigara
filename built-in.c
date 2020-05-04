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
