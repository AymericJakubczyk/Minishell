/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:07:31 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/25 03:33:36 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			no_whitespaces(char	*array);
static int	is_num(char *str);
int			do_overflow(char *str);
static int	count_args(t_parse *parse);
static void	next_exit(int runner, t_parse *parse, \
			t_list **my_env, t_exec *data);

static int	count_args(t_parse *parse)
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

static int	is_num(char *str)
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

void	ft_exit(t_parse *parse, t_list **my_env, \
		char **arg, t_exec *data)
{
	int	runner;
	int	count;

	count = count_args(parse);
	runner = 1;
	if (arg != NULL)
		free_all(arg);
	while (parse[runner].str)
	{
		next_exit(runner, parse, my_env, data);
		runner++;
	}
	if (count > 1)
		ft_error(ERROR_23, "exit", 1);
	free_all(data->str_heredoc);
	free(data->all_limiter);
	ft_dprintf("here");
	ft_lstclear(my_env, free);
	free_all_parse(data->parse);
	rl_clear_history();
	exit(g_errno);
}

static void	next_exit(int runner, t_parse *parse, \
		t_list **my_env, t_exec *data)
{
	long long	arg;
	int			count;

	count = count_args(parse);
	if (parse[runner].type == CMD_ARG)
	{
		arg = ft_atoll(parse[runner].str, my_env, data);
		if (!do_overflow(parse[runner].str) && \
			!is_num(parse[runner].str) && count <= 1)
		{
			g_errno = arg;
			free_all_parse(data->parse);
			ft_lstclear(my_env, free);
			rl_clear_history();
			exit(arg);
		}
		else if ((is_num(parse[runner].str) == 1 && runner == 1) || \
				do_overflow(parse[runner].str))
		{
			ft_error(ERROR_18, "exit", 2);
			ft_lstclear(my_env, free);
			free_all_parse(data->parse);
			free_all(data->str_heredoc);
			rl_clear_history();
			exit(2);
		}
	}
}

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
