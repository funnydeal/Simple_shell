#include "shell.h"

/**
 * _strcpy - copies a string
 * @destination: destination
 * @source: source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *source)
{
	int m = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[m])
	{
		destination[m] = source[m];
		m++;
	}
	destination[m] = 0;
	return (destination);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *duplicated;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	duplicated = malloc(sizeof(char) * (length + 1));
	if (!duplicated)
		return (NULL);
	for (length++; length--;)
		duplicated[length] = *--str;
	return (duplicated);
}

/**
 *_puts - prints an input string
 *@input: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *input)
{
	int m = 0;

	if (!input)
		return;
	while (input[m] != '\0')
	{
		_putchar(input[m]);
		m++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @char_input: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char char_input)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (char_input == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (char_input != BUF_FLUSH)
		buffer[index++] = char_input;
	return (1);
}
