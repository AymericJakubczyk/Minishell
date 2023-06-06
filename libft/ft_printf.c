/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:05:38 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/12/13 10:23:53 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	after(size_t i, const char *str, va_list va, ssize_t *count);

int	ft_printf(const char *str, ...)
{
	va_list	va;
	size_t	i;
	ssize_t	count;
	size_t	stock;

	i = 0;
	count = 0;
	stock = 0;
	va_start(va, str);
	while (str[i] && count != -1)
	{
		if (str[i] == '%')
		{
			if (str[i + 1])
				stock = after(i + 1, str, va, &count);
			if (stock == 1)
				i++;
		}
		else
			ft_putchar(str[i], &count);
		i++;
	}
	va_end(va);
	return (count);
}

static size_t	after(size_t i, const char *str, va_list va, ssize_t *count)
{
	if (str[i] == 'c')
		return (ft_putchar(va_arg(va, int), count), 1);
	if (str[i] == 's')
		return (ft_putstr(va_arg(va, char *), count), 1);
	if (str[i] == 'd' || str[i] == 'i')
		return (ft_putnbr(va_arg(va, int), count), 1);
	if (str[i] == 'u')
		return (ft_putunbr(va_arg(va, unsigned int), count), 1);
	if (str[i] == 'x')
		return (ft_put_hexa(va_arg(va, size_t), "0123456789abcdef", count), 1);
	if (str[i] == 'X')
		return (ft_put_hexa(va_arg(va, size_t), "0123456789ABCDEF", count), 1);
	if (str[i] == 'p')
	{
		ft_putstr("0x", count);
		return (ft_putptr_hexa(va_arg(va, size_t), count), 1);
	}
	if (str[i] == '%')
		return (ft_putchar(str[i], count), 1);
	return (0);
}
