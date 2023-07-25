#include "shell.h"

/**
 * is_chain - test if current char in buffer is a command delimiter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @pos: address of current position in buffer
 *
 * Return: 1 if command delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buffer, size_t *pos)
{
	size_t n = *pos;

	if (buffer[n] == '|' && buffer[n + 1] == '|')
	{
		buffer[n] = 0;
		n++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[n] == '&' && buffer[n + 1] == '&')
	{
		buffer[n] = 0;
		n++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[n] == ';') /* found end of this command */
	{
		buffer[n] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = n;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buffer: the char buffer
 * @pos: address of current position in buffer
 * @start: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buffer,
		size_t *pos, size_t start, size_t length)
{
	size_t n = *pos;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[start] = 0;
			n = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[start] = 0;
			n = length;
		}
	}

	*pos = n;
}

/**
 * replace_alias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 if not
 */
int replace_alias(info_t *info)
{
	int m;
	list_t *node;
	char *p;

	for (m = 0; m < 10; m++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int m = 0;
	list_t *node;

	for (m = 0; info->argv[m]; m++)
	{
		if (info->argv[m][0] != '$' || !info->argv[m][1])
			continue;

		if (!_strcmp(info->argv[m], "$?"))
		{
			replace_string(&(info->argv[m]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[m], "$$"))
		{
			replace_string(&(info->argv[m]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[m][1], '=');
		if (node)
		{
			replace_string(&(info->argv[m]),

					_strdup(_strchr(node->str, '=') + 1));

			continue;

		}

		replace_string(&info->argv[m], _strdup(""));


	}

	return (0);

}


/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old, char *new)

{
	free(*old);

	*old = new;

	return (1);

}



