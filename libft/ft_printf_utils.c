/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:23:12 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/12/12 13:33:25 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, ssize_t *count)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', count);
		n *= -1;
	}
	if (n / 10 == 0)
		ft_putchar(n + '0', count);
	else
	{
		c = n % 10 + '0';
		ft_putnbr(n / 10, count);
		ft_putchar(c, count);
	}
}

void	ft_putunbr(unsigned int n, ssize_t *count)
{
	char	c;

	if (n / 10 == 0)
		ft_putchar(n + '0', count);
	else
	{
		c = n % 10 + '0';
		ft_putunbr(n / 10, count);
		ft_putchar(c, count);
	}
}

void	ft_put_hexa(unsigned int nbr, char *base, ssize_t *count)
{
	if (nbr / 16 != 0)
	{
		ft_put_hexa(nbr / 16, base, count);
		ft_putchar(base[nbr % 16], count);
	}
	else if (nbr / 16 == 0)
		ft_putchar(base[nbr], count);
}

void	ft_putptr_hexa(size_t nbr, ssize_t *count)
{
	char	*base;

	base = "0123456789abcdef";
	if (nbr / 16 != 0)
	{
		ft_putptr_hexa(nbr / 16, count);
		ft_putchar(base[nbr % 16], count);
	}
	else if (nbr / 16 == 0)
		ft_putchar(base[nbr], count);
}
