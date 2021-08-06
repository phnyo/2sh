#include "./twosh.h"

int twosh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	//if pid == 0, then the executed thread is a child's one
	if (pid == 0)
	{
		// function template; int execvp(const char *file, char *const argv[]); 
		// this function takes filename and arguments starting from the filename 
		// (same as const char** argv in the main function) and executes it
		// -1 is the error code

		if (execvp(args[0], args) == -1)
		{
			perror("twosh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("twosh");
	}
	else
	{
		//parent process
		do {

		// the pid value of waitpid function is defined as follows:
		// <-1 wait till any child process with abs. value of process group id exits
		// -1 wait till any child processes exits
		// 0 ?? 
		// >0 wait for child process with pid to exit
		//
		// &status is the value of the status of the child process
		// WUNTRACED option allows the process to continue regardless of the state of the child process 
		
			wpid = waitpid(pid, &status, WUNTRACED);

		// WIFEXITED and WIFSIGNALED aka W(ait)IFEXITED and W(ait)IFSIGNALED is defined in #<sys/wait.h>
		// WIFEXITED will return 1 if the child process exits successfully (I suppose)
		// WIFSIGNALED will return 1 if the child process is interrupted by the signal (smth line <C-r>-c)

		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

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


