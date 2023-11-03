#include "main.h"

/**
 * split_command - splits the commands entered by the user
 * @str: commands entered by user
 *
 * Return: pointer to a pointer of words
 */

char **split_command(char *string)
{
	char **result = malloc(sizeof(char*) * strlen(string));
	char *token = strtok(string, " ");
	int i = 0;

	if (result == NULL)
	{
		perror("Error allocating memory");
		free(result);
		exit(EXIT_FAILURE);
	}
	while (token != NULL)
	{
		result[i++] = token;
		token = strtok(NULL, " ");
	}
	result[i] = NULL;
	return (result);
}

/**
 * execute - shifts the process to execute another program
 * @array: list of the commands that are passed to the prompt
 *
 * Return: NOthing
 */

void execute(char *array[], char *const *environment)
{
	pid_t pid = fork();
	(void)environment;

	if (pid == -1)
	{
		perror("Fork Failed!");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(array[0], array, NULL) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}

/**
 * main - initiates the program
 *
 * Return: int to show succces in implimenting the program
 */

int main(int ac, char *argv[], char *envp[])
{
	char *command = NULL;
	size_t len = 0;
	char **array = NULL;
	ssize_t line_size = 0;

	(void)ac;
	(void)argv;
	array = malloc(1024 * sizeof(char *));
	if (array == NULL)
	{
		perror("Error allocating memory for array");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		prompt();
		line_size = getline(&command, &len, stdin);
		if (line_size < 0)
			break;
		if (command[line_size - 1] == '\n')
			command[line_size - 1] = '\0';
		array = split_command(command);
		if (array == NULL)
		{
			perror("Error splitting command.");
			free(command);
			free(array);
			exit(EXIT_FAILURE);
		}
		execute(array, (char *const *)envp);
		free(array);
	}
	return (0);
}
