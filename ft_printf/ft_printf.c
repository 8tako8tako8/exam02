#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int	width = 0;
int	precision = 0;
int	is_precision = 0;
int	minus = 0;
char	number[] = "0123456789abcdef";
int	count = 0;


int	ft_strlen(char *s)
{
	int	i = 0;

	while (s[i])
		i++;
	return i;
}

int	ft_atoi(char **fmt)
{
	int	res = 0;

	while ('0' <= **fmt && **fmt <= '9')
	{
		res = res * 10 + (**fmt - '0');
		(*fmt)++;
	}
	return res;
}

void	print_s(char *s)
{
	int	i = 0;
	int	len;

	len = ft_strlen(s);
	if (is_precision && precision < len)
		len = precision;
	if (width > len)
	{
		while (width - len > i)
		{
			write(1, " ", 1);
			count++;
			i++;
		}
	}
	while (len--)
	{
		write(1, s++, 1);
		count++;
	}
}

int	count_digit(long dx, int base)
{
	int	i = 1;

	while (dx /= base)
		i++;
	return i;
}


void	print_dx_num(long dx, int base)
{
	if (dx < base)
	{
		write(1, number + dx, 1);
		count++;
	}
	else
	{
		print_dx_num(dx / base, base);
		print_dx_num(dx % base, base);
	}
}

void	print_dx(long dx, int base)
{
	int	digit;
	int	i = 0;

	if (dx == 0 && is_precision == 1 && precision == 0)
		return ;
	if (dx < 0)
	{
		minus = 1;
		dx *= -1;
	}
	digit = count_digit(dx, base);
	if (precision > digit)
	{
		if (width > precision + minus)
		{
			while (width - precision - minus > i)
			{
				write(1, " ", 1);
				count++;
				i++;
			}
		}
		if (minus)
		{
			write(1, "-", 1);
			count++;
		}
		i = 0;
		while (precision - digit > i)
		{
			write(1, "0", 1);
			count++;
			i++;
		}
	}
	else if (width > digit + minus)
	{
		i = 0;
		while (width - digit - minus > i)
		{
			write(1, " ", 1);
			count++;
			i++;
		}
		if (minus)
		{
			write(1, "-", 1);
			count++;
		}
	}
	else if (minus)
	{
		write(1, "-", 1);
		count++;
	}
	print_dx_num(dx, base);
}

void	print_percent(char **fmt, va_list ap)
{
	long	dx;
	char	*s;

	(*fmt)++;
	if ('0' <= **fmt && **fmt <= '9')
		width = ft_atoi(fmt);
	if (**fmt == '.')
	{
		(*fmt)++;
		is_precision = 1;
		precision = ft_atoi(fmt);
	}
	if (**fmt == 'd')
	{
		dx = va_arg(ap, int);
		print_dx(dx, 10);
		(*fmt)++;
	}
	else if (**fmt == 'x')
	{
		dx = va_arg(ap, unsigned int);
		print_dx(dx, 16);
		(*fmt)++;
	}
	else if (**fmt == 's')
	{
		s = va_arg(ap, char *);
		if (!s)
			s = "(null)";
		print_s(s);
		(*fmt)++;
	}
}

void	print_not_percent(char **fmt)
{
	while (**fmt && **fmt != '%')
	{
		write(1, *fmt, 1);
		(*fmt)++;
		count++;
	}
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	count = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		width = 0;
		precision = 0;
		is_precision = 0;
		minus = 0;
		if (*fmt == '%')
			print_percent((char **)&fmt, ap);
		else
			print_not_percent((char **)&fmt);
	}
	va_end(ap);
	return count;
}

#ifdef TEST
#include <stdio.h>

int main(void)
{
	int		ret1;
	int		ret2;
	ret1 = ft_printf("[%d][%d][%d][%d]", 123, 0, -123, 2147483647);
	ret2 = printf("[%d][%d][%d][%d]", 123, 0, -123, 2147483647);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%x][%x][%x][%x]", 0, 42, 5454, 2147483647);
	ret2 = printf("[%x][%x][%x][%x]", 0, 42, 5454, 2147483647);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%s][%s][%s][%s]", "", "hoge", "aaa", NULL);
	ret2 = printf("[%s][%s][%s][%s]", "", "hoge", "aaa", NULL);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%0d][%0d][%0d][%0d][%0d][%0d][%0d][%0d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%0d][%0d][%0d][%0d][%0d][%0d][%0d][%0d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%4d][%4d][%4d][%4d][%4d][%4d][%4d][%4d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%4d][%4d][%4d][%4d][%4d][%4d][%4d][%4d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%10d][%10d][%10d][%10d][%10d][%10d][%10d][%10d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%10d][%10d][%10d][%10d][%10d][%10d][%10d][%10d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%.0d][%.0d][%.0d][%.0d][%.0d][%.0d][%.0d][%.0d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%.0d][%.0d][%.0d][%.0d][%.0d][%.0d][%.0d][%.0d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%.4d][%.4d][%.4d][%.4d][%.4d][%.4d][%.4d][%.4d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%.4d][%.4d][%.4d][%.4d][%.4d][%.4d][%.4d][%.4d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%.10d][%.10d][%.10d][%.10d][%.10d][%.10d][%.10d][%.10d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%.10d][%.10d][%.10d][%.10d][%.10d][%.10d][%.10d][%.10d]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%0x][%0x][%0x][%0x][%0x][%0x][%0x][%0x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%0x][%0x][%0x][%0x][%0x][%0x][%0x][%0x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%4x][%4x][%4x][%4x][%4x][%4x][%4x][%4x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%4x][%4x][%4x][%4x][%4x][%4x][%4x][%4x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%10x][%10x][%10x][%10x][%10x][%10x][%10x][%10x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%10x][%10x][%10x][%10x][%10x][%10x][%10x][%10x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%.0x][%.0x][%.0x][%.0x][%.0x][%.0x][%.0x][%.0x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%.0x][%.0x][%.0x][%.0x][%.0x][%.0x][%.0x][%.0x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%.4x][%.4x][%.4x][%.4x][%.4x][%.4x][%.4x][%.4x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%.4x][%.4x][%.4x][%.4x][%.4x][%.4x][%.4x][%.4x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%.10x][%.10x][%.10x][%.10x][%.10x][%.10x][%.10x][%.10x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ret2 = printf("[%.10x][%.10x][%.10x][%.10x][%.10x][%.10x][%.10x][%.10x]", 0, 42, 1, 5454, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%4s][%4s][%4s][%4s]", "", "hoge", "aaa", NULL);
	ret2 = printf("[%4s][%4s][%4s][%4s]", "", "hoge", "aaa", NULL);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%10s][%10s][%10s][%10s]", "", "hoge", "aaa", NULL);
	ret2 = printf("[%10s][%10s][%10s][%10s]", "", "hoge", "aaa", NULL);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%.0s][%.0s][%.0s][%.0s]", "", "hoge", "aaa", NULL);
	ret2 = printf("[%.0s][%.0s][%.0s][%.0s]", "", "hoge", "aaa", NULL);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%.4s][%.4s][%.4s][%.4s]", "", "hoge", "aaa", NULL);
	ret2 = printf("[%.4s][%.4s][%.4s][%.4s]", "", "hoge", "aaa", NULL);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	ret1 = ft_printf("[%.10s][%.10s][%.10s][%.10s]", "", "hoge", "aaa", NULL);
	ret2 = printf("[%.10s][%.10s][%.10s][%.10s]", "", "hoge", "aaa", NULL);
	printf("\n");
	printf("%d,", ret1);
	printf("%d\n", ret2);

	return (0);
}
#endif
