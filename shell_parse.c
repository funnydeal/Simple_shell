#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(__attribute__((unused))info_t *info, char *path)
{
	struct stat st;

	if (path == NULL || stat(path, &st) != 0)
		return (0);

	if (st.st_mode & S_IFREG)
		return (1);

	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int m, f;

	for (m = start, f = 0; m < stop; m++)
	{
		if (pathstr[m] != ':')
			buf[f++] = pathstr[m];
	}
	buf[f] = '\0';

	return (buf);
}

/**
 * find_path - find this cmd in the PATH string
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int m, curr_pos;
	char *path;

	if (pathstr == NULL)
		return (NULL);
	if (_strlen(cmd) > 2 && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	for (m = 0, curr_pos = 0; pathstr[m] != '\0'; m++)
	{
		if (pathstr[m] == ':')
		{
			path = dup_chars(pathstr, curr_pos, m);
			if (*path == '\0')
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			curr_pos = m;
		}
	}
	return (NULL);
}
