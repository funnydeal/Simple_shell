#include "shell.h"

/**
 **_strncpy - this copies a string
 *@dest: destination string that will be copied to
 *@src: the source string
 *@n: the number of characters that will be copied
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int m, j;
	char *s = dest;

	m = 0;
	while (src[m] != '\0' && m < n - 1)
	{
		dest[m] = src[m];
		m++;
	}
	if (m < n)
	{
		j = m;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: maximum number of bytes to be used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int m, j;
	char *s = dest;

	m = 0;
	j = 0;
	while (dest[m] != '\0')
		m++;
	while (src[j] != '\0' && j < n)
	{
		dest[m] = src[j];
		m++;
		j++;
	}
	if (j < n)
		dest[m] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: string to be parsed
 *@c: character to locate
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
