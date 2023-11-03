#include "main.h"

/**
 * _isatty - helps determine whether or not to print "$ "
 * @f_descriptor: File description
 * 
 * Return: returns an integer (in this case, a boolean-like integer,
 * where 0 usually means false and any non-zero value means true).
 */

int my_isatty(int f_descriptor)
{
	struct stat buf;

	return (fstat(f_descriptor, &buf) == 0 && S_ISCHR(buf.st_mode));
}

/**
 * prompt - displays "$ " and waits for the user to type a command
 *
 * Reuturn: Nothing
 */

void prompt(void)
{
	/*if (my_isatty(STDOUT_FILENO) && (STDIN_FILENO))*/
		write(STDERR_FILENO, "$ ", 2);
}
