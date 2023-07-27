/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:46:17 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/27 14:03:54 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_builtin(t_parse *parse, t_list **my_env, int runner, \
								t_exec *data);
static void	handle_forked_single_builtin(t_parse *parse, t_list **my_env, \
											int runner, t_exec *data);
static void	next_handle_forked_single_builtin(t_parse *parse, t_list **my_env, \
											int runner);
static void	exec_single_cmd(t_parse *parse, t_list **env, int runner, \
								t_exec *data);

void	single_cmd(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	runner;

	runner = 0;
	if (!check_all_redirect_without_fork(parse, my_env))
	{
		g_errno = 1;
		return ;
	}
	while (parse[runner].str)
	{
		if (parse[runner].type == COMMAND)
		{
			if (which_builtin(parse, runner) == 1)
			{
				if (handle_single_builtin(parse, my_env, runner, data) == 1)
					return ;
			}
			else if (which_builtin(parse, runner) == 2)
				handle_forked_single_builtin(parse, my_env, runner, data);
			else
				exec_single_cmd(parse, my_env, runner, data);
		}
		runner++;
	}
}

static int	handle_single_builtin(t_parse *parse, t_list **my_env, int runner, \
									t_exec *data)
{
	if (ft_strcmp(parse[runner].str, "cd") == 0)
		ft_cd(my_env, parse);
	else if (ft_strcmp(parse[runner].str, "unset") == 0)
		ft_unset(my_env, parse);
	else if (ft_strcmp(parse[runner].str, "exit") == 0)
	{
		ft_exit(parse, my_env, NULL, data);
		return (1);
	}
	else if (ft_strcmp(parse[runner].str, "export") == 0)
		ft_export(my_env, parse);
	return (0);
}

static void	handle_forked_single_builtin(t_parse *parse, t_list **my_env, \
											int runner, t_exec *data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		exit (1);
	else if (pid == 0)
	{
		if (redirect_in_cmd(parse, IN))
			do_redirect_in(parse, my_env, data, 1);
		if (redirect_in_cmd(parse, OUT))
			do_redirect_out(parse, my_env, data);
		if (ft_strcmp(parse[runner].str, "export") == 0)
			ft_export(my_env, parse);
		else
			next_handle_forked_single_builtin(parse, my_env, runner);
		free_minishell(data, my_env);
		double_close(&data->fd_in, &data->fd_out);
		exit (g_errno);
	}
	double_close(&data->fd_in, &data->fd_out);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		g_errno = WEXITSTATUS(status);
}

static void	next_handle_forked_single_builtin(t_parse *parse, t_list **my_env, \
											int runner)
{
	char	*path;

	if (ft_strcmp(parse[runner].str, "echo") == 0)
		return (ft_echo(parse));
	else if (ft_strcmp(parse[runner].str, "env") == 0)
		ft_env(my_env, parse);
	else if (ft_strcmp(parse[runner].str, "pwd") == 0)
	{
		if (find_arg(parse) == -1)
			return ;
		path = ft_pwd(1);
		if (!path)
			return ;
		else 
		{
			ft_printf("%s\n", path);
			free(path);
		}
	}
}

static void	exec_single_cmd(t_parse *parse, t_list **env, int runner, \
								t_exec *data)
{
	int	pid;
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (redirect_in_cmd(parse, IN))
			do_redirect_in(parse, env, data, 1);
		if (redirect_in_cmd(parse, OUT))
			do_redirect_out(parse, env, data);
		ex_child(parse, env, runner, data);
		double_close(&data->fd_in, &data->fd_out);
		exit(0);
	}
	waitpid(-1, &status, 0);
	verif_status(status);
}
