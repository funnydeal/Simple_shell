#include "shell.h"
/**
 * bfree - Frees a pointer and sets the pointer to NULL
 * @ptr: Pointer to the address of the pointer to be freed
 *
 * Return: 1 if successful, 0 otherwise
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
