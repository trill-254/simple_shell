#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>

extern char **environ;

int prompt(void);
void _strcat(char *dest, const char *src);
void _strcpy(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strlen(const char *str);
char **split_command(char *string);
char *_getenv(const char *name);
void execute(char *array[], char *const *environment);

#endif
