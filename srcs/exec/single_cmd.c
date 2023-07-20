/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:46:17 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/21 01:08:36 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_builtin(t_parse *parse, t_list **my_env, int runner);
void	handle_forked_single_builtin(t_parse *parse, \
		t_list **my_env, int runner);
void	next_handle_forked_single_builtin(t_parse *parse, \
		t_list **my_env, int runner);
void	exec_single_cmd(t_parse *parse, t_list **env, int runner, t_exec *data);

void	single_cmd(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	runner;

	pipe(data->pipes);
	runner = 0;
	if (!check_all_redirect(parse, my_env))
		return ;
	while (parse[runner].str)
	{
		if (parse[runner].type == HEREDOC)
			data->current_fd_in = dup_in(parse, runner, data, my_env);
		if (parse[runner].type == INFILE)
			data->current_fd_in = dup_in(parse, runner, data, my_env);
		if (parse[runner].type == OUTFILE)
			data->current_fd_out = dup_out(parse, runner, my_env);
		runner++;
	}
	double_close(&data->pipes[0], &data->pipes[1]);
	single_cmd_execution(parse, my_env, data);
	double_close(&data->current_fd_in, &data->current_fd_out);
}

void	handle_single_builtin(t_parse *parse, t_list **my_env, int runner)
{
	if (ft_strcmp(parse[runner].str, "cd") == 0)
		ft_cd(my_env, parse);
	else if (ft_strcmp(parse[runner].str, "unset") == 0)
		ft_unset(my_env, parse);
	else if (ft_strcmp(parse[runner].str, "exit") == 0)
		ft_exit(parse);
	else if (ft_strcmp(parse[runner++].str, "export") == 0)
		ft_export(my_env, parse);
	return ;
}

void	handle_forked_single_builtin(t_parse *parse, \
		t_list **my_env, int runner)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		if (ft_strcmp(parse[runner].str, "export") == 0)
			ft_export(my_env, parse);
		else
			next_handle_forked_single_builtin(parse, my_env, runner);
		exit (0);
	}
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		g_errno = WEXITSTATUS(status);
}

void	next_handle_forked_single_builtin(t_parse *parse, \
		t_list **my_env, int runner)
{
	if (ft_strcmp(parse[runner].str, "echo") == 0)
		return (ft_echo(parse));
	else if (ft_strcmp(parse[runner].str, "env") == 0)
		ft_env(my_env);
	else if (ft_strcmp(parse[runner].str, "pwd") == 0)
		ft_printf("%s\n", ft_pwd(1));
}

void	exec_single_cmd(t_parse *parse, t_list **env, int runner, t_exec *data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		ex_child(parse, env, runner, data);
		double_close(&data->fd_in, &data->fd_out);
		exit(0);
	}
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		g_errno = WEXITSTATUS(status);
}
