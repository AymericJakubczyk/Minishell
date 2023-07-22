/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:07:31 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/22 04:30:54 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		no_whitespaces(char	*array);
int		is_num(char *str);
static void	count_args(t_parse *parse, t_list **my_env);

static void	count_args(t_parse *parse, t_list **my_env)
{
	int	runner;
	int	count;

	count = 0;
	runner = 0;
	while (parse[runner].type != PIPEE && parse[runner].str)
	{
		if (parse[runner].type == CMD_ARG)
		{
			if (is_num(parse[runner].str) != 0)
			{
				free_all_parse(parse);
				ft_lstclear(my_env, free);
				rl_clear_history();
				ft_error(ERROR_21, "exit", 2);
				exit(2);
			}
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
	int	arg;

	if (parse[runner].type == CMD_ARG)
	{
		arg = ft_atoi(parse[runner].str);
		if (arg != 0)
		{
			g_errno = arg;
			print_parse(parse);
			// free_all_parse(parse);
			ft_lstclear(my_env, free);
			rl_clear_history();
			exit(arg);
		}
		else
		{
			ft_error(ERROR_21, "exit", 2);
			ft_lstclear(my_env, free);
			free_all_parse(parse);
			rl_clear_history();
			exit(2);
		}
	}
}
