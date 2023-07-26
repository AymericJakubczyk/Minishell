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

static void	exec_cmd(t_parse *parse, int num_cmd, \
		t_list **my_env, t_exec *data);
int			get_start_cmd(t_parse *parse, int num_cmd);
char		*get_str_cmd(t_parse *parse);
static void	wait_all(int nbr_cmd, t_exec *data);
void			do_fork(t_parse *parse,int num_cmd, t_list **my_env, t_exec *data);

void	exec_with_forks(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	nbr_cmd;
	int	num_cmd;

	nbr_cmd = how_many_cmds(parse) + 1;
	data->all_pid = malloc(sizeof(int) * nbr_cmd);
	if (!data->all_pid)
		return (ft_error(ERROR_42, NULL, 2));
	data->nbr_cmd = nbr_cmd;
	data->prec_fd = 0;
	num_cmd = 0;
	while (num_cmd < nbr_cmd)
	{
		pipe(data->pipes);
		do_fork(parse, num_cmd, my_env, data);
		num_cmd++;
	}
	if (data->prec_fd)
		close(data->prec_fd);
	close(data->pipes[0]);
	close(data->pipes[1]);
	wait_all(nbr_cmd, data);
	// if (data->str_heredoc != NULL)
	// 	free_all(data->str_heredoc);
	// if (data->all_limiter)
	// 	free(data->all_limiter);
	free(data->all_pid);
}

void	do_fork(t_parse *parse,int num_cmd, t_list **my_env, t_exec *data)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		ft_dprintf("error pid\n");
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		free(data->all_pid);
		exec_cmd(parse, num_cmd, my_env, data);
		if (data->str_heredoc != NULL)
			free_all(data->str_heredoc);
		if (data->all_limiter)
			free(data->all_limiter);
		free_all_parse(parse);
		ft_lstclear(my_env, free);
		rl_clear_history();
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
//don't forget to secure pipe;

static void	exec_cmd(t_parse *parse, int num_cmd, t_list **my_env, t_exec *data)
{
	char	**arg;
	char	*path;
	int		start_cmd;

	start_cmd = get_start_cmd(parse, num_cmd);
	if (!check_all_redirect(&parse[start_cmd], my_env, data))
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
	if (!arg)
		return ;
	if (do_builtin(&parse[start_cmd], my_env, arg, data))
	{
		ft_lstclear(my_env, free);
		free_all(arg);
		rl_clear_history();
		free_all_parse(parse);
		exit(0);
	}
	path = get_path(arg[0], my_env, parse);
	if (!path)
		return ;
	// double_close(&data->fd_in, &data->fd_out);
	execve(path, arg, data->env);
	if (ft_strlen(get_str_cmd(&parse[start_cmd])) != 0)
	{
		ft_error(strerror(errno), get_str_cmd(&parse[start_cmd]), errno);
		exit(g_errno);
	}
	else
	{
		ft_error(ERROR_12, "\'\'", 127);
		exit(g_errno);
	}
}

char *get_str_cmd(t_parse *parse)
{
	int i;

	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == COMMAND)
			return (parse[i].str);
		i++;
	}
	return (NULL);
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
