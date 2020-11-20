#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int			width = 0;
int			precision = 0;
int			is_precision = 0;
int			neg = 0;
char		digits[] = "0123456789abcdef";
int			count = 0;

int		count_digit(long num, int base)
{
	int		i;

	i = 1;
	while (num /= base)
		i++;
	return (i);
}

int		ft_strlen(char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int			is_number(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int			ft_atoi(char **fmt)
{
	int			res;

	res = 0;
	while (is_number(**fmt))
	{
		res = res * 10 + (**fmt - 48);
		(*fmt)++;
	}
	return (res);
}

void		print_int_base(long dx, int base)
{
	if (dx < base)
	{
		write(1, digits + dx, 1);
		count++;
	}
	else
	{
		print_int_base(dx / base, base);
		print_int_base(dx % base, base);
	}
}

void		print_int_fmt(long dx, int base)
{
	int		len;
	int		i;

	if (dx < 0)
	{
		neg = 1;
		dx *= (-1);
	}
	len = count_digit(dx, base);
	i = 0;
	if (precision > len)
	{
		if (width > precision + neg)
		{
			while (i++ < width - precision - neg)
			{
				write(1, " ", 1);
				count++;
			}
				
		}
		if (neg)
		{
			write(1, "-", 1);
			count++;
		}
		i = 0;
		while (i++ < precision - len)
		{
			write(1, "0", 1);
			count++;
		}
	}
	else if (width > len + neg)
	{
		while (i++ < width - len - neg)
		{
			write(1, " ", 1);
			count++;
		}
		if (neg)
		{
			write(1, "-", 1);
			count++;
		}
	}
	else if (neg)
	{
		write(1, "-", 1);
		count++;
	}
	print_int_base(dx, base);
}

void		print_str(char *s)
{
	int			i = 0;
	int			len;

	len = ft_strlen(s);
	if (is_precision && precision < len)
		len = precision;
	if (width > len)
	{
		while (i++ < width - len)
		{
			write(1, " ", 1);
			count++;
		}
	}
	while (len--)
	{
		write(1, s++, 1);
		count++;
	}
}

void		print_by_fmt(char **fmt, va_list ap)
{
	long			dx;
	char			*s;

	(*fmt)++;
	if (is_number(**fmt))
		width = ft_atoi(fmt);
	if (**fmt == '.')
	{
		is_precision = 1;
		(*fmt)++;
		precision = ft_atoi(fmt);
	}
	if (**fmt == 'd')
	{
		dx = va_arg(ap, int);
		print_int_fmt(dx, 10);
		(*fmt)++;
	}
	else if (**fmt == 'x')
	{
		dx = va_arg(ap, unsigned int);
		print_int_fmt(dx, 16);
		(*fmt)++;
	}
	else if (**fmt == 's')
	{
		s = va_arg(ap, char *);
		if (!s)
			s = "(null)";
		print_str(s);
		(*fmt)++;
	}
}

void		print_to_percent(char **fmt)
{
	while (**fmt && **fmt != '%')
	{
		write(1, *fmt, 1);
		(*fmt)++;
		count++;
	}
}

int			ft_printf(const char *fmt, ... )
{
	va_list			ap;

	va_start(ap, fmt);
	count = 0;
	while (*fmt)
	{
		width = 0;
		precision = 0;
		is_precision = 0;
		neg = 0;
		if (*fmt == '%')
			print_by_fmt((char **)&fmt, ap);
		else
			print_to_percent((char **)&fmt);
	}
	va_end(ap);
	return (count);
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