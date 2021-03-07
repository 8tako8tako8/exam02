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

void	ft_inter(char *s1, char *s2)
{
	int		i,j,k;
	char	inter[255] = {};

	inter[0] = '\0';
	i = 0;
	k = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j] && ft_strchr(inter, s1[i]) == 0)
				inter[k++] = s1[i];
			j++;
		}
		i++;
	}
	inter[k] = '\0';
	k = 0;
	while (inter[k])
	{
		write(1, &inter[k], 1);
		k++;
	}
}

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		ft_inter(argv[1], argv[2]);
	}
	write(1, "\n", 1);

	return 0;
}
