#include "./twosh.h"

char** twosh_split_line(char* line)
{
	int bufsize = TWOSH_TOK_BUFSIZE;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;
	int position = 0;
	
	if (!tokens)
	{
		fprintf(stderr, "twosh: allocation failed at twosh_split_line at line 6 \n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TWOSH_TOK_DELIM);
	while(token)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += TWOSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "twosh: allocation failed at twosh_split_line at line 25\n");
				exit(EXIT_FAILURE);
			}
		}
		//s1 == NULL if strtok is called more than once
		token = strtok(NULL, TWOSH_TOK_DELIM);
	}
	tokens[position] = token;
	return tokens;
}

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


