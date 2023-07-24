/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:46:17 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/24 03:13:21 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	next_handle_forked_single_builtin(t_parse *parse, \
		t_list **my_env, int runner);
void	exec_single_cmd(t_parse *parse, t_list **env, int runner, t_exec *data);

void	single_cmd(t_parse *parse, t_list **my_env, t_exec *data)
{
	single_cmd_execution(parse, my_env, data);
}

void	handle_single_builtin(t_parse *parse, t_list **my_env, int runner, t_exec *data)
{
	// if (!check_all_redirect_without_fork(parse, my_env))
	// 	return ;
	if (ft_strcmp(parse[runner].str, "cd") == 0)
		ft_cd(my_env, parse);
	else if (ft_strcmp(parse[runner].str, "unset") == 0)
		ft_unset(my_env, parse);
	else if (ft_strcmp(parse[runner].str, "exit") == 0)
		ft_exit(parse, my_env, NULL, data);
	else if (ft_strcmp(parse[runner].str, "export") == 0)
		ft_export(my_env, parse);
	return ;
}

void	handle_forked_single_builtin(t_parse *parse, \
		t_list **my_env, int runner, t_exec *data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		// if (!check_all_redirect(parse, my_env, data))
		// 	exit (1);
		if (redirect_in_cmd(parse, IN))
			do_redirect_in(parse, my_env, data, 1);
		if (redirect_in_cmd(parse, OUT))
			do_redirect_out(parse, my_env, data);
		if (ft_strcmp(parse[runner].str, "export") == 0)
			ft_export(my_env, parse);
		else
			next_handle_forked_single_builtin(parse, my_env, runner);
		ft_lstclear(my_env, free);
		free_all_parse(parse);
		rl_clear_history();
		double_close(&data->fd_in, &data->fd_out);
		exit (g_errno);
	}
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		g_errno = WEXITSTATUS(status);
}

void	next_handle_forked_single_builtin(t_parse *parse, \
		t_list **my_env, int runner)
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

void	exec_single_cmd(t_parse *parse, t_list **env, int runner, t_exec *data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		// if (!check_all_redirect(parse, env, data))
		// 	exit (1);
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
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, handler_fork);
		signal(SIGQUIT, handler_fork_slash);
	}
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		g_errno = WEXITSTATUS(status);
}

int	find_arg(t_parse *parse)
{
	int	runner;
	int	index;

	index = 0;
	runner = 0;
	while (parse[runner].str)
	{
		if (parse[runner].type == CMD_ARG)
			if (parse[runner].str[index] == '-')
			{
				while(parse[runner].str[index])
					index++;
				if (index == 2 && parse[runner].str[0] == '-' && parse[runner].str[1] == '-')
					return (0);
				if (index >= 2)
					return (ft_error(ERROR_25, parse[runner].str, 2), -1);
				index = 0;
			}
		runner++;
	}
	return (0);
}
