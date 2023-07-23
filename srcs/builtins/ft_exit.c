/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:07:31 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/23 03:19:01 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		no_whitespaces(char	*array);
int		is_num(char *str);
int		do_overflow(char *str);
static void	count_args(t_parse *parse, t_list **my_env);

static void	count_args(t_parse *parse, t_list **my_env)
{
	int	runner;
	int	count;

	count = 0;
	runner = 0;
	(void) my_env;
	while (parse[runner].type != PIPEE && parse[runner].str)
	{
		if (parse[runner].type == CMD_ARG)
		{
			// if (is_num(parse[runner].str) != 0)
			// {
			// 	free_all_parse(parse);
			// 	ft_lstclear(my_env, free);
			// 	rl_clear_history();
			// 	ft_error(ERROR_18, "exit", 2);
			// 	exit(2);
			// }
			count++;
		}
		runner++;
	}
	if (count > 1)
		return (ft_error(ERROR_23, "exit", 1), exit(g_errno));
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

void	ft_exit(t_parse *parse, t_list **my_env, char **arg)
{
	int	runner;
	runner = 0;
	if (arg != NULL)
		free_all(arg);
	count_args(parse, my_env);
	while (parse[runner].str)
	{
		next_exit(runner, parse, my_env);
		runner++;
	}
	ft_lstclear(my_env, free);
	free_all_parse(parse);
	rl_clear_history();
	exit(1);
}

void	next_exit(int runner, t_parse *parse, t_list **my_env)
{
	long long	arg;

	if (parse[runner].type == CMD_ARG)
	{
		arg = ft_atoll(parse[runner].str);
		if (arg != 0 && !do_overflow(parse[runner].str))
		{
			g_errno = arg;
			free_all_parse(parse);
			ft_lstclear(my_env, free);
			rl_clear_history();
			exit(arg);
		}
		else
		{
			ft_error(ERROR_18, "exit", 2);
			ft_lstclear(my_env, free);
			free_all_parse(parse);
			rl_clear_history();
			exit(2);
		}
	}
}

int	do_overflow(char *str)
{
	int	i;
	int	sign;
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
		if (to_return * sign != (to_return * sign * 10 + (str[i] - '0') * sign) / 10)
			return (1);
		to_return = to_return * 10 + str[i] - '0';
		i++;
	}
	return (0);
}
