/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:05:38 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/23 00:52:53 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintf(const char *str, ...)
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
				stock = dafter(i + 1, str, va, &count);
			if (stock == 1)
				i++;
		}
		else
			ft_dputchar(str[i], &count);
		i++;
	}
	va_end(va);
	return (count);
}

size_t	dafter(size_t i, const char *str, va_list va, ssize_t *count)
{
	if (str[i] == 'c')
		return (ft_dputchar(va_arg(va, int), count), 1);
	if (str[i] == 's')
		return (ft_dputstr(va_arg(va, char *), count), 1);
	if (str[i] == 'd' || str[i] == 'i')
		return (ft_dputnbr(va_arg(va, int), count), 1);
	if (str[i] == 'u')
		return (ft_dputunbr(va_arg(va, unsigned int), count), 1);
	if (str[i] == 'x')
		return (ft_dput_hexa(va_arg(va, size_t), "0123456789abcdef", count), 1);
	if (str[i] == 'X')
		return (ft_dput_hexa(va_arg(va, size_t), "0123456789ABCDEF", count), 1);
	if (str[i] == 'p')
	{
		ft_dputstr("0x", count);
		return (ft_dputptr_hexa(va_arg(va, size_t), count), 1);
	}
	if (str[i] == '%')
		return (ft_dputchar(str[i], count), 1);
	return (0);
}
