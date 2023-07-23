/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:06:00 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/23 00:51:56 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dputnbr(int n, ssize_t *count)
{
	char	c;

	if (n == -2147483648)
	{
		ft_dputstr("-2147483648", count);
		return ;
	}
	if (n < 0)
	{
		ft_dputchar('-', count);
		n *= -1;
	}
	if (n / 10 == 0)
		ft_dputchar(n + '0', count);
	else
	{
		c = n % 10 + '0';
		ft_dputnbr(n / 10, count);
		ft_dputchar(c, count);
	}
}

void	ft_dputunbr(unsigned int n, ssize_t *count)
{
	char	c;

	if (n / 10 == 0)
		ft_dputchar(n + '0', count);
	else
	{
		c = n % 10 + '0';
		ft_dputunbr(n / 10, count);
		ft_dputchar(c, count);
	}
}

void	ft_dput_hexa(unsigned int nbr, char *base, ssize_t *count)
{
	if (nbr / 16 != 0)
	{
		ft_dput_hexa(nbr / 16, base, count);
		ft_dputchar(base[nbr % 16], count);
	}
	else if (nbr / 16 == 0)
		ft_dputchar(base[nbr], count);
}

void	ft_dputptr_hexa(size_t nbr, ssize_t *count)
{
	char	*base;

	base = "0123456789abcdef";
	if (nbr / 16 != 0)
	{
		ft_dputptr_hexa(nbr / 16, count);
		ft_dputchar(base[nbr % 16], count);
	}
	else if (nbr / 16 == 0)
		ft_dputchar(base[nbr], count);
}
