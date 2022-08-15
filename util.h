#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 5
int get_line(FILE *fp, char **buffer);
void strip_blanks(char *buffer);
void strip_comments(char *buffer);
char get_last_chr(char *buffer);
char **tokenize(char *line);
#endif