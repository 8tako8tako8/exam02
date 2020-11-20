#include <unistd.h>

void	ft_putstr(char *s)
{
	int	i = 0;

	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

int	ft_strchr_ex(char *s, char c)
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

void	inter(char *s1, char *s2)
{
	int	i, j, k;
	char	INTER[255];

	INTER[0] = '\0';
	i = 0;
	k = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j] && (ft_strchr_ex(INTER, s1[i]) == 0))
				INTER[k++] = s1[i];
			j++;
		}
		i++;
	}
	INTER[k] = '\0';
	ft_putstr(INTER);
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return 0;
}
