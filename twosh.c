#include "./twosh.h"

void twosh_loop(void)
{
	char *line;
	char **args;
	int status = 1;

	do {
		printf("$ ");
		line = twosh_read_line();
		args = twosh_split_line(line);
		//status = 2sh_execute(args);
		free(line);
		free(args);
	} while (status);
}

int main(int argc, char **argv)
{
	twosh_loop();	
	return EXIT_SUCCESS;
}
