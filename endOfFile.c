#include "main.h"

/**
 * end_of_file - executes ctrl d
 * @array: pointer to an array of strings
 *
 * Return: Nothing;
 */

void end_of_file(char **array)
{
	(void)array;

	/*write(1, \n 1);*/
	exit(EXIT_SUCCESS);
}
