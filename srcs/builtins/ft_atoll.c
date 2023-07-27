/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:46:25 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/27 15:26:36 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoll(const char *str, t_list **my_env, t_exec *data)
{
	size_t		i;
	int			sign;
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
		if (str[++i] == '+' || str[i] == '-')
		{
			ft_error(ERROR_18, "exit", 2);
			free_minishell(data, my_env);
			exit(2);
		}
	}
	to_return = is_overflow(&str[i], sign);
	return (to_return);
}

long long	is_overflow(const char *str, int sign)
{
	int			i;
	long long	to_return;

	to_return = 0;
	i = 0;
	if (sign == 2)
		sign = 1;
	else
		i = 0;
	while (ft_isdigit(str[i]))
	{
		if (to_return * sign != \
			(to_return * sign * 10 + (str[i] - '0') * sign) / 10)
			return (1);
		to_return = to_return * 10 + (str[i] - '0');
		i++;
	}
	return (to_return * sign);
}
