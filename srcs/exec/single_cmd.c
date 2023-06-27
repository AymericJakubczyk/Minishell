/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:46:17 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/27 19:51:53 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_builtin(t_parse *parse, t_list **my_env, int runner);
void	handle_forked_single_builtin(t_parse *parse, t_list **my_env, int runner);
void	next_handle_forked_single_builtin(t_parse *parse, t_list **my_env, int runner, char *arg);
void	exec_single_cmd(t_parse *parse, t_list **env, int runner);

void	single_cmd(t_parse *parse, t_list **my_env)
{
	int	runner;

	runner = 0;
	while (parse[runner].str)
	{
		// if (parse[runner].type == INFILE)
			// dup_in(parse, runner)
		// if (parse[runner].type == OUTFILE)
			// dup_out(parse, runner);
		if (parse[runner].type == COMMAND)
		{
			if (which_builtin(parse, runner) == 1)
				handle_single_builtin(parse, my_env, runner);
			else if (which_builtin(parse, runner) == 2)
				handle_forked_single_builtin(parse, my_env, runner);
			else
				exec_single_cmd(parse, my_env, runner);
		}
		runner++;
	}
}

void	handle_single_builtin(t_parse *parse, t_list **my_env, int runner)
{
	if (ft_strcmp(parse[runner].str, "cd") == 0)
	{
		if (parse[runner + 2].str && parse[runner + 2].type == CMD_ARG)
			ft_error(ERROR_23, parse[runner].str);
		ft_cd(parse[++runner].str, my_env);
	}
	if (ft_strcmp(parse[runner].str, "unset") == 0)
		ft_unset(my_env, parse[++runner].str);
	if (ft_strcmp(parse[runner].str, "export") == 0)
	{
		while (parse[++runner].str && parse[runner].type == CMD_ARG)
			ft_export(my_env, parse[runner].str);
	}
	return ;
}

void	handle_forked_single_builtin(t_parse *parse, t_list **my_env, int runner)
{
	int		pid;
	char	*arg;

	arg = NULL;
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		if (ft_strcmp(parse[runner].str, "export") == 0)
			ft_export(my_env, parse[++runner].str);
		else
			next_handle_forked_single_builtin(parse, my_env, runner, arg);
		exit (1);
	}
	waitpid(-1, NULL, 0);
}

void	next_handle_forked_single_builtin(t_parse *parse, t_list **my_env, int runner, char *arg)
{
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
		return ;
	}
	if (ft_strcmp(parse[runner].str, "env") == 0)
	{
		if (parse[runner + 1].str && ft_strcmp(parse[runner + 1].str, "|") != 0)
			return ;
		ft_env(my_env);
	}
}

void	exec_single_cmd(t_parse *parse, t_list **env, int runner)
{
	int		pid;

	pid = fork();
	if (pid == -1)
	{
		exit(1);
	}
	if (pid == 0)
	{
		ex_child(parse, env, runner);
		exit(1);
	}
	waitpid(pid, NULL, 0);
}