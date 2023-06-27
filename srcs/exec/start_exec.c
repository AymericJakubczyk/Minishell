/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:05:40 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/27 12:53:46 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_parse *parse, t_list **my_env, int runner);

void	start_exec(t_parse *parse, t_list **my_env)
{
	int	runner;
	int	type;
	int	pid;

	runner = 0;
	// type = do_i_fork(parse);
	// if (type == 1)
	while (parse[runner].str)
	{
		if (parse[runner].type && parse[runner].type == COMMAND)
		{
			runner = is_builtin(parse, my_env, runner);
		}
		runner++;
	}
}

int	do_i_fork(t_parse *parse)
{
	int	runner;

	runner = 0;
	while (parse[runner].str)
	{
		if (parse[runner].str[0] && parse[runner].str[0] == '|')
			return (1);
		runner++;
	}
	return (0);
}

//return 2 if fork is needed
int	which_builtin(t_parse *parse, int runner)
{
	if (ft_strcmp(parse[runner].str, "echo") == 0)
		return (2);
	if (ft_strcmp(parse[runner].str, "env") == 0)
		return (2);
	if (ft_strcmp(parse[runner].str, "pwd") == 0)
		return (2);
	if (ft_strcmp(parse[runner].str, "export") == 0)
	{
		if (parse[runner + 1].type == CMD_ARG)
			return (1);
		else
			return (2);
	}
	if (ft_strcmp(parse[runner].str, "exit") == 0)
		return (1);
	if (ft_strcmp(parse[runner].str, "unset") == 0)
		return (1);
	if (ft_strcmp(parse[runner].str, "cd") == 0)
		return (1);
	return (0);
}

int	is_builtin(t_parse *parse, t_list **my_env, int runner)
{
	char	*arg;

	arg = NULL;
	if (ft_strcmp(parse[runner].str, "echo") == 0)
	{
		if (parse[++runner].str && parse[runner].type == CMD_ARG)
			arg = ft_strdup(parse[runner].str);
		while (parse[++runner].type == CMD_ARG)
		{
			arg = ft_strjoin3(arg, " ");
			arg = ft_strjoin3(arg, parse[runner].str);
		}
		ft_echo(arg);
		return (runner);
	}
	if (ft_strcmp(parse[runner].str, "export") == 0)
	{
		ft_export(my_env, parse[++runner].str);
		return (runner);
	}
	runner = next_is_builtin(parse, my_env, runner);
	return (runner);
}

int	next_is_builtin(t_parse *parse, t_list **my_env, int runner)
{
	if (ft_strcmp(parse[runner].str, "unset") == 0)
		ft_unset(my_env, parse[++runner].str);
	if (ft_strcmp(parse[runner].str, "pwd") == 0)
		ft_printf("%s\n",ft_pwd());
	if (ft_strcmp(parse[runner].str, "env") == 0)
	{
		if (parse[runner + 1].str && ft_strcmp(parse[runner + 1].str, "|") != 0)
			return (runner);
		ft_env(my_env);
	}
	if (ft_strcmp(parse[runner].str, "cd") == 0)
	{
		if (parse[runner + 2].str && parse[runner + 2].type == CMD_ARG)
			ft_error(ERROR_23, parse[runner].str);
		ft_cd(parse[++runner].str, my_env);
	}
	return (runner);
}
