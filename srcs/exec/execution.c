/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:38:49 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/24 14:30:07 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	how_much_args(t_parse *parse, int runner);

void	print_all_data(char **all_limiter, char **str_heredoc)
{
	int	i;

	i = 0;
	while (all_limiter[i])
	{
		ft_printf("limiter %d : %s \nSTRING : \n%sFIN STR\n", \
		i, all_limiter[i], str_heredoc[i]);
		i++;
	}
}

void	execution(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	pipes;

	data->parse = parse;
	if (heredoc_in(parse))
	{
		do_heredoc(parse, data, my_env);
		if (g_errno == 130)
			return ;
	}
	pipes = how_many_cmds(parse);
	if (pipes != 0)
		exec_with_forks(parse, my_env, data);
	else
		single_cmd(parse, my_env, data);
}

int	how_many_cmds(t_parse *parse)
{
	int	runner;
	int	count;

	count = 0;
	runner = 0;
	while (parse[runner].str)
	{
		if (parse[runner].type == PIPEE)
			count++;
		runner++;
	}
	return (count);
}

void	ex_child(t_parse *parse, t_list **env, int runner, t_exec *data)
{
	char	**arg;
	char	*path;
	int		index;

	index = 0;
	arg = NULL;
	path = get_path(parse[runner].str, env, parse);
	if (!path)
		return ;
	arg = get_arg(parse);
	if (execve(path, arg, data->env) == -1)
	{
		if (ft_strlen(parse[runner].str) != 0)
		{
			ft_error(strerror(errno), parse[runner].str, errno);
			exit(g_errno);
		}
		else
		{
			ft_error(ERROR_12, "\'\'", 127);
			exit(g_errno);
		}
	}
}

// static int	how_much_args(t_parse *parse, int runner)
// {
// 	int	index;

// 	index = 0;
// 	while (parse[runner].str && parse[runner].type)
// 	{
// 		index++;
// 		runner++;
// 	}
// 	return (index);
// }
