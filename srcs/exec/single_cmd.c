/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:46:17 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/30 14:28:05 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_builtin(t_parse *parse, t_list **my_env, int runner);
void	handle_forked_single_builtin(t_parse *parse, t_list **my_env, int runner);
void	next_handle_forked_single_builtin(t_parse *parse, t_list **my_env, int runner, char *arg);
void	exec_single_cmd(t_parse *parse, t_list **env, int runner, t_exec *data);

void	single_cmd(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	runner;
	int	pipes[2];

	pipe(pipes);
	runner = 0;
	while (parse[runner].str)
	{
		if (parse[runner].type == HEREDOC)
			data->current_fd_in = dup_in(parse, runner, pipes, data);
		if (parse[runner].type == INFILE)
			data->current_fd_in = dup_in(parse, runner, pipes, data);
		if (parse[runner].type == OUTFILE)
			data->current_fd_out = dup_out(parse, runner);
		runner++;
	}
	double_close(pipes[0], pipes[1]);
	single_cmd_execution(parse, my_env, data);
	double_close(data->current_fd_in, data->current_fd_out);
	// restore_dup(file, data, pipes[0]);
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
	if (ft_strcmp(parse[runner++].str, "export") == 0)
	{
		while (parse[runner].str && parse[runner].type == CMD_ARG)
		{
			ft_export(my_env, parse[runner].str);
			runner++;
		}
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

void	exec_single_cmd(t_parse *parse, t_list **env, int runner, t_exec *data)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		ex_child(parse, env, runner, data);
		double_close(data->fd_in, data->fd_out);
		exit(1);
	}
	waitpid(pid, NULL, 0);
}
