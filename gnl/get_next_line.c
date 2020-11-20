#include "get_next_line.h"

int	ft_stdin_or_read_file(char **line, char **save, int fd)
{
	ssize_t		read_size;
	int		flag = 0;
	char		*buf;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	while (flag == 0 && (read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		flag = ft_find_line(line, save, buf);
	}
	free(buf);
	return flag;
}

int	ft_find_line(char **line, char **save, char *buf)
{
	size_t	find_line;
	int	flag = 0;
	char	*tmp1;
	char	*tmp2;

	tmp2 = NULL;
	find_line = ft_strchr_ex(buf, '\n');
	tmp1 = ft_strjoin_ex(*line, buf, find_line);
	free(*line);
	*line = tmp1;
	if (buf[find_line] == '\n')
	{
		tmp2 = ft_strdup(buf + find_line + 1);
		flag = 1;
	}
	free(*save);
	*save = tmp2;
	return flag;
}

int	get_next_line(int fd, char **line)
{
	static char	*save;
	int		flag = 0;

	if (fd < 0 || line == NULL)
		return (-1);
	*line = (char *)malloc(1);
	*line[0] = '\0';
	if (save != NULL)
		flag = ft_find_line(line, &save, save);
	if (flag == 0)
		flag = ft_stdin_or_read_file(line, &save, fd);
	return flag;
}

/* int	ft_read_error(char **line, char **save)
{
	free(*line);
	free (*save);
	return (-1);
} */

/* size_t	ft_strlen(char *s)
{
	size_t	i = 0;

	while (s[i] != '\0')
		i++;
	return i;
}

char	*ft_strdup(char *s)
{
	int	len;
	char	*str;

	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	len = 0;
	while (s[len] != '\0')
	{
		str[len] = s[len];
		len++;
	}
	str[len] = '\0';
	return str;
}

void	ft_strlcpy_ex(char *dst, char *src, size_t dstsize)
{
	size_t	i = 0;

	if (dstsize == 0)
		return ;
	while (src[i] != '\0' && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_strjoin_ex(char *s1, char *s2, size_t len2)
{
	size_t	len1;
	char	*str;

	len1 = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	ft_strlcpy_ex(str, s1, len1);
	ft_strlcpy_ex(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}

size_t	ft_strchr_ex(char *s, char c)
{
	size_t	i;

	while (s[i] != '\0')
	{
		if (s[i] == c)
			return i;
		i++;
	}
	return i;
}
 */