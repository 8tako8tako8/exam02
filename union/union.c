#include <unistd.h>

int	ft_strchr(char *s, char c)
{
	int	i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return 1;
		i++;
	}
	return 0;
}

void	ft_union(char *s1, char *s2)
{
	int		i,j,k;
	char	c[255] = {};

	i = 0;
	j = 0;
	k = 0;
	while (c[i])
	{
		c[i] = '\0';
		i++;
	}
	i = 0;
	while (s1[i])
	{
		if (ft_strchr(c, s1[i]) == 0)
			c[k++] = s1[i];
		i++;
	}
	while (s2[j])
	{
		if (ft_strchr(c, s2[j]) == 0)
			c[k++] = s2[j];
		j++;
	}
	c[k] = '\0';
	i = 0;
	while (c[i])
	{
		write(1, &c[i], 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc == 3)
		ft_union(argv[1], argv[2]);
	write(1, "\n", 1);

	return 0;
}
