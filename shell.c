#include "main.h"

/**
 * main - initiates the program
 * @ac: no use in the program
 * @argv: no use in the program
 * @envp: helps in implementing clear command
 *
 * Return: int to show succces in implimenting the program
 */

int main(int ac, char *argv[], char *envp[])
{
	char *command = NULL;
	size_t len = 0;
	char **array = NULL;
	ssize_t line_size = 0;

	(void)argv;
	(void)ac;
	array = malloc(1024 * sizeof(char *));
	if (array == NULL)
	{
		perror("Error allocating memory for array");
		exit(EXIT_SUCCESS); }
	while (1)
	{
		prompt();
		line_size = getline(&command, &len, stdin);
		if (line_size == -1 || line_size == EOF)
		{
			free(command);
			end_of_file(array); }
		if (line_size <= 0)
			break;
		if (command[line_size - 1] == '\n')
			command[line_size - 1] = '\0';
		if (command[0] == '\n' || command[0] == '\0')
			continue;
		array = split_command(command);
		if (array == NULL)
		{
			perror("Error splitting command.");
			free(command);
			exit(EXIT_FAILURE); }
		if (_strncmp(array[0], "exit", 4) == 0)
		{
			free(command);
			free(array);
			exit(0); }
		else
			execute(array, (char *const *)envp);
		free(array); }
	return (0); }
