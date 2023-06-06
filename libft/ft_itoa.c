/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:19:05 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/11/22 13:20:38 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_int(int n);

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = len_int(n);
	str = malloc(sizeof(char) * (i + 1));
	if (str == 0)
		return (0);
	str[i] = 0;
	i--;
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n / 10 != 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	str[i] = n % 10 + '0';
	return (str);
}

static int	len_int(int n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n / 10 != 0)
	{
		size++;
		n = n / 10;
	}
	size++;
	return (size);
}
