#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i = 0;

	while (s[i])
		i++;
	return i;
}

int	ft_strchr(char *s, char c)
{
	int	i = 0;
	
	while (s[i])
	{
		if (s[i] == c)
			return i;
		i++;
	}
	return i;
}

void	ft_strlcpy(char *dst, char *src, int dstsize)
{
	int	i = 0;

	if (dstsize == 0)
		return ;
	while (src[i] && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_strdup(char *s)
{
	itn	len;
	int	i = 0;
	char	*str;

	len = ft_strlen(s);
	str = (char *)malloc(len + 1);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return str;
}

char	*ft_strjoin(char *s1, char *s2, int len2)
{
	int	len1;
	char	*str;

	len1 = ft_strlen(s1);
	str = (char *)malloc(len1 + len2 + 1);
	ft_strlcpy(str, s1, len1);
	ft_strlcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return str;
}

int	ft_find_line(cha **line, char **save, char *buf)
{
	size_t		find_line;
	int		flag = 0;
	char		*tmp1;
	char		*tmp2;

	tmp2 = NULL;
	find_line = ft_strchr(buf, '\n');
	tmp1 = ft_strjoin(*line, buf, find_line);
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

int	ft_stdin(char **line, char **save)
{
	ssize_t		read_size;
	int		flag = 0;
	char 		*buf;
	
	buf = (char *)malloc(BUFFER_SIZE + 1);
	while (flag == 0 && (read_size = read(0, buf, BUFFER_SIZE)) > 0)
	{
		buf[BUFFER_SIZE] = '\0';
		flag = ft_find_line(line, save, buf);
	}
	free(buf);
	return flag;
}

int	get_next_line(char **line)
{
	static char	*save;
	int		flag = 0;

	if (line == NULL)
		return -1;
	*line = (char *)malloc(1);
	*line[0] = '\0';
	if (save != NULL)
		flag = ft_find_line(line, &save, save);
	if (flag == 0)
		flag = ft_stdin(line, &save);
	return flag;
}
