#include "get_next_line.h"

size_t	ft_strlen(char *s)
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
	return str;
}

size_t	ft_strchr_ex(char *s, char c)
{
	size_t	i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == c)
			return i;
		i++;
	}
	return i;
}