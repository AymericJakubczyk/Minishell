/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:07:31 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/26 02:43:20 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	next_exit(int runner, t_parse *parse, \
			t_list **my_env, t_exec *data);

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
	free_minishell(data, my_env);
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
			free_minishell(data, my_env);
			exit(arg);
		}
		else if ((is_num(parse[runner].str) == 1 && runner == 1) || \
			do_overflow(parse[runner].str))
		{
			ft_error(ERROR_18, "exit", 2);
			free_minishell(data, my_env);
			exit(2);
		}
	}
}

void	free_minishell(t_exec *data, t_list **my_env)
{
	if (data->str_heredoc)
		free_all(data->str_heredoc);
	if (data->all_limiter)
		free(data->all_limiter);
	free_all_parse(data->parse);
	ft_lstclear(my_env, free);
	rl_clear_history();
}
