/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:54:15 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/11/22 13:20:38 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c);

int	ft_atoi(const char *str)
{
	size_t	i;
	int		signe;
	long	to_return;

	i = 0;
	signe = 1;
	to_return = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (to_return != (to_return * 10 + (str[i] - '0')) / 10 && signe == -1)
			return (0);
		if (to_return != (to_return * 10 + (str[i] - '0')) / 10 && signe == 1)
			return (-1);
		to_return = to_return * 10 + str[i] - '0';
		i++;
	}
	return (to_return * signe);
}

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\v' || c == '\n')
		return (1);
	if (c == '\r' || c == '\f' || c == ' ')
		return (1);
	return (0);
}
