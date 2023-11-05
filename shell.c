#include "main.h"

/**
 * _strlen - counts the lenght of a string and returns the number
 * @str: string whose length is to be determined
 *
 * Return: length of the string
 */
int _strlen(const char *str)
{
	int len = 0;
	while (*str != '\0')
	{
		len++;
		str++;
	}
	return len;
}

/**
 * _strncmp - compares two strings
 * @s1: one of the strings
 * @s2: the other string
 *
 * Returns: 0 if s1 & s2 are same, negative No is s2 < s1,
 * positive No otherwise
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}
	return (0);
}

/**
 * _strcpy - copies one string to another
 * @dest: where string is to be copied to
 * @src: where string is to be copied from
 *
 * Return: Nothing
 */

void _strcpy(char *dest, const char *src)
{
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

/**
 * _strcat - concatenates two strings
 * @dest: string to be added another string
 * @src: source of string to be concatenated
 *
 * Return: Nothing
 */

void _strcat(char *dest, const char *src)
{
	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

/**
 * split_command - splits the commands entered by the user
 * @str: commands entered by user
 *
 * Return: pointer to a pointer of words
 */

char **split_command(char *string)
{
	char **result = malloc(sizeof(char*) * _strlen(string));
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
 * _getenv - gets the environment
 * @name: name of the environment
 *
 * Return: environment of the given name
 */

char *_getenv(const char *name)
{
	int i, len = _strlen(name);
	
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
		{
			return (environ[i] + len + 1);
		}
	}
	return (NULL);
}

/**
 * execute - shifts the process to execute another program
 * @array: list of the commands that are passed to the prompt
 *
 * Return: Nothing
 */

void execute(char *array[], char *const *environment)
{
	int status;
	char *path, *token;
	struct stat st;
	char command_path[1024];

	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork Failed!");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (array[0][0] == '/')
		{
			if (stat(array[0], &st) == 0 && S_ISREG(st.st_mode))
			{
				if (execve(array[0], array, environment) == -1)
				{
					perror("./shell");
					exit(EXIT_FAILURE);
				}
			}
		}
		else
		{
			path = _getenv("PATH");
			token = strtok(path, ":");
		
			while (token != NULL)
			{
				_strcpy(command_path, token);
				_strcat(command_path, "/");
				_strcat(command_path, array[0]);
				if (stat(command_path, &st) == 0 && S_ISREG(st.st_mode))
				{
					if (execve(command_path, array, environment) == -1)
					{
						perror("./shell");
						exit(EXIT_FAILURE);
					}
				}
				token = strtok(NULL, ":");
			}
		write(STDERR_FILENO, "Command not found: ", 19);
		write(STDERR_FILENO, array[0], _strlen(array[0]));
		write(STDERR_FILENO, "\n", 1);
		exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, &status, 0);
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

	(void)argv;
	(void)ac;
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
		if (line_size <= 0)
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
