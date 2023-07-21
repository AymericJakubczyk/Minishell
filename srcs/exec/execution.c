/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:38:49 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/18 18:35:58 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	how_much_args(t_parse *parse, int runner);
// static void	print_tab(char **tab);

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
	int		count;

	count = 0;
	index = 0;
	arg = NULL;
	count = how_much_args(parse, runner);
	path = get_path(parse[runner].str, env);
	if (!path)
		return ;
	arg = malloc(sizeof(char *) * (count + 1));
	if (!arg)
		ft_printf("Malloc error in ex_child\n");
	arg[index++] = ft_strdup(parse[runner++].str);
	if (!arg[index - 1])
		ft_printf("Malloc error in ex_child\n");
	while (parse[runner].str && parse[runner].type == CMD_ARG)
	{
		arg[index] = ft_strdup(parse[runner++].str);
		if (!arg[index++])
			ft_printf("Malloc error in ex_child\n");
	}
	arg[index] = NULL;
	if (execve(path, arg, data->env) == -1)
		return ;
}

static int	how_much_args(t_parse *parse, int runner)
{
	int	index;

	index = 0;
	while (parse[runner].str && parse[runner].type)
	{
		index++;
		runner++;
	}
	return (index);
}

// static void	print_tab(char **tab)
// {
// 	int	runner;

// 	runner = 0;
// 	while (tab[runner])
// 	{
// 		ft_printf("%s\n", tab[runner]);
// 		runner++;
// 	}
// }
