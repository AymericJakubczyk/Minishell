/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:46:25 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/23 04:20:56 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(char c);

long long	ft_atoll(const char *str)
{
	size_t	i;
	int		sign;
	long long	to_return;

	i = 0;
	sign = 1;
	to_return = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '+')
			sign = 2;
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	to_return = is_overflow(str, sign);
	return (to_return);
}

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\v' || c == '\n')
		return (1);
	if (c == '\r' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

long long	is_overflow(const char *str, int sign)
{
	int	i;
	long long	to_return;

	to_return = 0;
	if (sign == -1)
		i = 1;
	else if (sign == 2)
	{
		sign = 1;
		i = 1;
	}
	else
		i = 0;
	while (ft_isdigit(str[i]))
	{
		if (to_return * sign != (to_return * sign * 10 + (str[i] - '0') * sign) / 10)
			return (1);
		to_return = to_return * 10 + (str[i] - '0');
		i++;
	}
	return (to_return * sign);
}
