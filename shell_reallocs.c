#include "shell.h"
/**
 * _memset - fills memory with a constant byte
 * @s: pointer to the memory area
 * @b: byte to fill *s with
 * @n: amount of bytes to be filled
 *
 * Return: (s) a pointer to the memory area s
 */
void *_memset(void *s, int b, size_t n)
{
	unsigned int m;

	for (m = 0; m < n; m++)
		((char *)s)[m] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to the previous malloc'ated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	_memset(p, 0, old_size);
	memcpy(p, ptr, old_size);
	free(ptr);
	return (p);
}
