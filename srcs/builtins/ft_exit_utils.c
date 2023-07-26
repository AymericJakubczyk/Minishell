/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:42:29 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/26 01:43:58 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_overflow(char *str)
{
	int			i;
	int			sign;
	long long	to_return;

	sign = 1;
	to_return = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (to_return * sign != \
			(to_return * sign * 10 + (str[i] - '0') * sign) / 10)
			return (1);
		to_return = to_return * 10 + str[i] - '0';
		i++;
	}
	return (0);
}

int	count_args(t_parse *parse)
{
	int	runner;
	int	count;

	count = 0;
	runner = 0;
	while (parse[runner].type != PIPEE && parse[runner].str)
	{
		if (parse[runner].type == CMD_ARG)
			count++;
		runner++;
	}
	return (count);
}

int	is_num(char *str)
{
	int	runner;

	runner = 0;
	while (str[runner])
	{
		if (runner == 0 && (str[runner] == '-' || str[runner] == '+'))
			runner++;
		if (ft_isdigit(str[runner]) != 1)
			return (1);
		runner++;
	}
	return (0);
}
