/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:14:56 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/22 17:00:08 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_parse *parse, int num_cmd, \
		t_list **my_env, t_exec *data);
int	get_start_cmd(t_parse *parse, int num_cmd);
static void	wait_all(int nbr_cmd);

void	exec_with_forks(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	nbr_cmd;
	int	num_cmd;
	int	pid;

	nbr_cmd = how_many_cmds(parse) + 1;
	data->nbr_cmd = nbr_cmd;
	data->prec_fd = 0;
	num_cmd = 0;
	while (num_cmd < nbr_cmd)
	{
		pipe(data->pipes);
		//signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == -1)
			ft_printf("error pid\n");
		else if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			exec_cmd(parse, num_cmd, my_env, data);
			exit(0);
		}
		else
		{
			signal(SIGINT, handler_fork);
			signal(SIGQUIT, handler_fork_slash);
			if (data->prec_fd)
				close(data->prec_fd);
			data->prec_fd = data->pipes[0];
			if (num_cmd == data->nbr_cmd - 1)
				close(data->pipes[0]);
			close(data->pipes[1]);
		}
		num_cmd++;
	}
	if (data->prec_fd)
		close(data->prec_fd);
	close(data->pipes[0]);
	close(data->pipes[1]);
	wait_all(nbr_cmd);
}
//don't forget to secure pipe;

void	handler_fork(int sig)
{
	(void) sig;
	ft_printf("\n");
	//exit(0);
}

void	handler_fork_slash(int sig)
{
	(void) sig;
	//dprintf(2, "TEST \\\n");
	ft_printf("Quit (core dumped)\n");
	//exit(0);
}

static void	exec_cmd(t_parse *parse, int num_cmd, t_list **my_env, t_exec *data)
{
	char	**arg;
	char	*path;
	int		start_cmd;

	start_cmd = get_start_cmd(parse, num_cmd);
	if (!check_all_redirect(&parse[start_cmd], my_env))
		exit (1);
	if (redirect_in_cmd(&parse[start_cmd], IN))
		do_redirect_in(&parse[start_cmd], my_env, data, num_cmd);
	else
		do_classique_pipe(num_cmd, data, IN);
	if (redirect_in_cmd(&parse[start_cmd], OUT))
		do_redirect_out(&parse[start_cmd], my_env, data);
	else
		do_classique_pipe(num_cmd, data, OUT);
	arg = get_arg(&parse[start_cmd]);
	if (do_builtin(parse, my_env, arg, num_cmd))
	{
		ft_lstclear(my_env, free);
		free_all(arg);
		rl_clear_history();
		free_all_parse(parse);
		exit(1);
	}
	path = get_path(arg[0], my_env, parse);
	// double_close(&data->fd_in, &data->fd_out);
	execve(path, arg, data->env);
}

int	get_start_cmd(t_parse *parse, int num_cmd)
{
	int	start;
	int	n_cmd;

	start = 0;
	n_cmd = 0;
	while (n_cmd < num_cmd && parse[start].str)
	{
		if (parse[start].type == PIPEE)
			n_cmd++;
		start++;
	}
	return (start);
}

static void	wait_all(int nbr_cmd)
{
	int	i;
	int	status;

	i = 0;
	while (i < nbr_cmd)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	if (WIFEXITED(status))
	{
		g_errno = WEXITSTATUS(status);
	}
}
