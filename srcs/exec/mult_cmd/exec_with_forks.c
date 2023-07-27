/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:14:56 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/26 06:04:16 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_fork(t_parse *parse, int num_cmd, t_list **my_env, t_exec *data);
static void	wait_all(int nbr_cmd, t_exec *data);

void	exec_with_forks(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	num_cmd;

	data->nbr_cmd = how_many_cmds(parse) + 1;
	data->all_pid = malloc(sizeof(int) * data->nbr_cmd);
	if (!data->all_pid)
		return (ft_error(ERROR_42, NULL, 2));
	data->prec_fd = 0;
	num_cmd = 0;
	while (num_cmd < data->nbr_cmd)
	{
		pipe(data->pipes);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		do_fork(parse, num_cmd, my_env, data);
		num_cmd++;
	}
	if (data->prec_fd)
		close(data->prec_fd);
	close(data->pipes[0]);
	close(data->pipes[1]);
	wait_all(data->nbr_cmd, data);
	free(data->all_pid);
}

static void	do_fork(t_parse *parse, int num_cmd, t_list **my_env, t_exec *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_dprintf("error pid\n");
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		free(data->all_pid);
		exec_cmd(parse, num_cmd, my_env, data);
		free_minishell(data, my_env);
		exit(0);
	}
	else
	{
		data->all_pid[num_cmd] = pid;
		if (data->prec_fd)
			close(data->prec_fd);
		data->prec_fd = data->pipes[0];
		if (num_cmd == data->nbr_cmd - 1)
			close(data->pipes[0]);
		close(data->pipes[1]);
	}
}

static void	wait_all(int nbr_cmd, t_exec *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < nbr_cmd)
	{
		waitpid(data->all_pid[i], &status, 0);
		i++;
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			g_errno = 130;
			ft_dprintf("\n");
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			g_errno = 131;
			ft_dprintf("Quit (core dumped)\n");
		}
	}
	if (WIFEXITED(status))
		g_errno = WEXITSTATUS(status);
}
