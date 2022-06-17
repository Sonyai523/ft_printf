/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarthric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:52:58 by rarthric          #+#    #+#             */
/*   Updated: 2021/11/15 17:53:01 by rarthric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void	ft_recurs_nbr(long long num, int *len)
{
	long long	num_write;

	if (num > 0)
	{
		ft_recurs_nbr(num / 10, len);
		num_write = num % 10 + 48;
		*len += write(1, &num_write, 1);
	}
}

static void	ft_recurs_hex(unsigned long long num, char type, int *len)
{
	unsigned long long	num_write;
	int					type_hex;

	if (type == 'X')
		type_hex = 55;
	if (type == 'x' || type == 'p')
		type_hex = 87;
	if (num > 0)
	{
		ft_recurs_hex(num / 16, type, len);
		num_write = num % 16;
		if (num_write <= 9)
			num_write = num_write + 48;
		else
			num_write = num_write + type_hex;
		*len += write(1, &num_write, 1);
	}
}

static void	ft_putnbrhex(long long num, char type, int *len)
{
	if (type == 'd' || type == 'i' || type == 'u')
	{
		if (num == 0)
			*len += write(1, "0", 1);
		if (num > 0)
			ft_recurs_nbr(num, len);
		if (num < 0)
		{
			*len += write(1, "-", 1);
			num *= -1;
			ft_recurs_nbr(num, len);
		}
	}
	if (type == 'p')
		num = (unsigned long long)num;
	if (type == 'x' || type == 'X' || type == 'p')
	{
		if (type == 'p')
			*len += write(1, "0x", 2);
		if (num == 0)
			*len += write(1, "0", 1);
		else
			ft_recurs_hex(num, type, len);
	}
}

static void	ft_print_arg(va_list arg, char type, int *len)
{
	char	s;
	char	*str;

	if (type == 'c')
	{
		s = va_arg(arg, int);
		*len += write(1, &s, 1);
	}
	else if (type == 's')
	{
		str = va_arg(arg, char *);
		if (str == NULL)
			*len += write(1, "(null)", 6);
		else
			while (*str)
				*len += write(1, str++, 1);
	}
	else if (type == 'd' || type == 'i')
		ft_putnbrhex(va_arg(arg, int), type, len);
	else if (type == 'x' || type == 'X' || type == 'u')
		ft_putnbrhex(va_arg(arg, unsigned int), type, len);
	else if (type == 'p')
		ft_putnbrhex(va_arg(arg, unsigned long long), type, len);
	else
		*len += write(1, &type, 1);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	arg;

	len = 0;
	va_start(arg, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1) != '\0')
		{
			str++;
			ft_print_arg(arg, *str, &len);
		}
		else
			len += write(1, str, 1);
		str++;
	}
	va_end(arg);
	return (len);
}
int main()
{
	ft_printf("jdkdkd%i", 12);

}