/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:46:25 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/24 01:30:03 by cprojean         ###   ########.fr       */
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
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '+')
			sign = 2;
		if (str[i] == '-')
			sign = -1;
		if (str[++i] == '+' || str[i] == '-')
		{
			ft_error(ERROR_18, "exit", 2);
			ft_lstclear(my_env, free);
			free_all_parse(data->parse);
			rl_clear_history();
			exit(2);
		}
	}
	to_return = is_overflow(str, sign);
	return (to_return);
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
