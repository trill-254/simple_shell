#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

#define BUFFER_SIZE 1024

/**
 * read_line - Reads a line from stdin
 * Return: Pointer to the read line
 */
char *read_line(void)
{
char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
if (!buffer)
{
perror("Allocation error");
exit(EXIT_FAILURE);
}

printf("#cisfun$ ");
if (!fgets(buffer, BUFFER_SIZE, stdin))
{
free(buffer);
return (NULL);
}

buffer[strcspn(buffer, "\n")] = '\0';
return (buffer);
}

/**
 * main - Simple Shell
 * Return: Always 0
 */
int main(void)
{
char *line;
pid_t child_pid;
int status;

do {
line = read_line();

if (line)
{
child_pid = fork();
if (child_pid == -1)
}
perror("fork error");
exit(EXIT_FAILURE);
}
if (child_pid == 0)
{
if (execlp(line, line, NULL) == -1)
{
perror("Error");
exit(EXIT_FAILURE);
}
}
else
{
wait(&status);
}

free(line);
}
}
while
(line) }
return (EXIT_SUCCESS);
}
