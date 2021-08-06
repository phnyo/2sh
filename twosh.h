#ifndef TWOSH_H
#define TWOSH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
	
#define TWOSH_RL_BUFSIZE 1024

#define TWOSH_TOK_BUFSIZE 1024
#define TWOSH_TOK_DELIM " \t\r\n\a"

char* twosh_read_line();
char** twosh_split_line(char* line);

#endif

