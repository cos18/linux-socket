#include "utils.h"

int set_new_str(char **line, char **save)
{
	int size;
	int locate;
	int result;
	char *tmp_str;

	size = 0;
	while ((*save)[size] && (*save)[size] != '\n')
		size++;
	*line = (char *)malloc(size + 1);
	locate = 0;
	while (locate < size)
	{
		(*line)[locate] = (*save)[locate];
		locate++;
	}
	(*line)[locate] = '\0';
	result = (((*save)[size] == '\n') ? READ : READ_EOF);
	tmp_str = (result ? ft_strpush(*save, size + 1) : NULL);
	if (result == READ_EOF && *save)
		free(*save);
	*save = tmp_str;
	return (result);
}

int error_handling(char **save)
{
	if (*save)
		free(*save);
	*save = NULL;
	return (ERROR);
}

int final_reset(char **line, char **save)
{
	*line = ft_strnul();
	if (*save)
		free(*save);
	*save = NULL;
	return (READ_EOF);
}

int get_next_line(int fd, char **line)
{
	long long len;
	char buff[READ_BUFFER + 1];
	static char *str[FD_SIZE];
	char *tmp_str;

	if (fd < 0 || !line || fd >= FD_SIZE ||
		READ_BUFFER <= 0 || read(fd, buff, 0))
		return (ERROR);
	if (!str[fd])
		str[fd] = ft_strnul();
	len = 0;
	while (!(ft_strchr(str[fd], '\n')) &&
		   ((len = read(fd, buff, READ_BUFFER)) > 0))
	{
		buff[len] = '\0';
		tmp_str = ft_strjoin(str[fd], buff);
		if (str[fd])
			free(str[fd]);
		str[fd] = tmp_str;
	}
	if (len < 0)
		return (error_handling(&(str[fd])));
	if (len == 0 && str[fd][0] == '\0')
		return (final_reset(line, &(str[fd])));
	return (set_new_str(line, &(str[fd])));
}
