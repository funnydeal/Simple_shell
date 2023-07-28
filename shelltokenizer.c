#include "shell.h"
/**
 * strtow - splits a string into words. Repeat delimiters are ignored.
 * @str: input string
 * @d: delimiter string
 * Return: a pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *d)
{
	int m, n, f, h, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (m = 0; str[m] != '\0'; m++)
		if (!is_delim(str[m], d) && (is_delim(str[m + 1], d) || !str[m + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));

	if (!s)
		return (NULL);
	for (m = 0, n = 0; n < numwords; n++)
	{
		while (is_delim(str[m], d))
			m++;
		f = 0;
		while (!is_delim(str[m + f], d) && str[m + f])
			f++;
		s[n] = malloc((f + 1) * sizeof(char));
		if (!s[n])
		{
			for (f = 0; f < n; f++)
				free(s[f]);
			free(s);
			return (NULL);
		}
		for (h = 0; h < f; h++)
			s[n][h] = str[m++];
		s[n][h] = 0;
	}
	s[n] = NULL;
	return (s);
}

/**
 * strtow2 - splits a string into words
 * @str: input string
 * @d: delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int m, n, f, h, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (m = 0; str[m] != '\0'; m++)
		if ((str[m] != d && str[m + 1] == d) ||
					(str[m] != d && !str[m + 1]) || str[m + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));

	if (!s)
		return (NULL);
	for (m = 0, n = 0; n < numwords; n++)
	{
		while (str[m] == d && str[m] != d)
			m++;
		f = 0;
		while (str[m + f] != d && str[m + f] && str[m + f] != d)
			f++;
		s[n] = malloc((f + 1) * sizeof(char));
		if (!s[n])
		{
			for (f = 0; f < n; f++)
				free(s[f]);
			free(s);
			return (NULL);
		}
		for (h = 0; h < f; h++)
			s[n][h] = str[m++];
		s[n][h] = 0;
	}
	s[n] = NULL;
	return (s);
}
