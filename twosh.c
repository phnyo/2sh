#include "./twosh.h"

char* twosh_read_line()
{
	char *line;
	ssize_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}
	return line;
}

void twosh_loop(void)
{
	char *line;
	char **args;
	int status = 1;

	do {
		printf("$ ");
		line = twosh_read_line();
		//args = 2sh_split_line(line);
		//status = 2sh_execute(args);
		free(line);
		while (*args)
		{
			free(*args);
			args++;
		}
	} while (status);
}

int main(int argc, char **argv)
{
	twosh_loop();	
	return EXIT_SUCCESS;
}
