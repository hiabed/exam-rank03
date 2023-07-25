#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	hexlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static int	len_num(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (!n)
		i++;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ntohex(unsigned int n)
{
	if (n >= 16)
	{
		ntohex(n / 16);
		ntohex(n % 16);
	}
	else if (n < 10)
		ft_putchar(n + '0');
	else if (n > 9 && n <= 15)
		ft_putchar(n + 87);
	return (hexlen(n));
}
int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
    if(n > 9)
    {
        ft_putnbr(n / 10);
        ft_putnbr(n % 10);
    }
    else if (n >= 0 && n <= 9)
    {
        ft_putchar(n + 48);
    }
    else if (n < 0)
    {
        ft_putnbr(-n);
    }
    else if (n == -2147483648)
        ft_putstr("-2147483648");
    return len_num(n);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		len;
	va_list	list;

	va_start(list, s);
	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
            i++;
            if (s[i] == 's')
		        len = len + ft_putstr(va_arg(list, char *));
        	else if (s[i] == 'd')
		        len = len + ft_putnbr(va_arg(list, int));
        	else if (s[i] == 'x')
		        len = len + ntohex(va_arg(list, unsigned int));
		}
		else if (s[i] != '%')
			len = len + ft_putchar(s[i]);
		i++;
	}
	va_end(list);
	return (len);
}

int main()
{
    ft_printf("%d\n", ft_printf("%d\n", 0));
    printf("%d\n", printf("%d\n", 0));
}