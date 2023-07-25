#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: the address of buffer
 * @len: the address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t u = 0;
	size_t len_p = 0;

	if (!len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		u = getline(buf, &len_p, stdin);
#else
		u = _getline(info, buf, &len_p);
#endif
		if (u > 0)
		{
			if ((*buf)[u - 1] == '\n')
			{
				(*buf)[u - 1] = '\0'; /* remove trailing newline */
				u--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			if (_strchr(*buf, ';'))
			{
				*len = u;
				info->cmd_buf = *buf;
			}
		}
	}
	return (u);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char buf; /* the ';' command chain buffer */
	static size_t m, n, len;
	ssize_t u = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	u = input_buf(info, (char **)&buf, &len);
	if (u == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		n = m; /* init new iterator to current buf position */
		p = (char *)(buf + m); /* get pointer for return */

		check_chain(info, &buf, &n, m, len);
		while (n < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, &buf, &n))
				break;
			n++;
		}

		m = n + 1; /* increment past nulled ';' */
		if (m >= len) /* reached end of buffer? */
		{
			m = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		buf_p = &p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of the current command */
	}

	*buf_p = &buf; /* else not a chain, pass back buffer from _getline() */
	return (u); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @m: size
 *
 * Return: u
 */
ssize_t read_buf(info_t *info, char *buf, size_t *m)
{
	ssize_t u = 0;

	if (*m)
		return (0);
	u = read(info->readfd, buf, READ_BUF_SIZE);
	if (u >= 0)
		*m = u;
	return (u);
}

/**
 * _getline - gets next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t m, len;
	size_t f;
	ssize_t u = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (m == len)
		m = len = 0;

	u = read_buf(info, buf, &len);
	if (u == -1 || (u == 0 && len == 0))
		return (-1);

	c = _strchr(buf + m, '\n');
	f = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + f : f + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + m, f - m);
	else
		_strncpy(new_p, buf + m, f - m + 1);

	s += f - m;
	m = f;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		_puts("\n");
		_puts("$ ");
		_putchar(BUF_FLUSH);
	}
}


