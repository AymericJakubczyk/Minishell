/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:31:47 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/30 19:38:08 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	each_cmd(t_parse *parse, t_list **my_env, t_exec *data, int *index);
void	piped_cmd_execution(t_parse *parse, t_list **my_env, t_exec *data, int runner);

void	exec_with_forks(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	pipes[2];
	int	*pid;
	int	index;
	int	count;

	count = how_many_pipes(parse);
	pid = malloc(sizeof(int *) * count);
	pipes[0] = 0;
	pipes[1] = 0;
	while (parse[index].str)
	{
		if (parse[index].type == PIPEE)
		{
			pipes[1] = index;
			// pipe(data->pipe);
			// pid[count] = fork();
			// if (pid[count] == 0)
			// {
			each_cmd(parse, my_env, data, pipes);
			double_close(data->pipe[0], data->pipe[1]);
			exit(0);
			count--;
			// }
			pipes[0] = pipes[1];
		}
		index++;
	}
}

void	each_cmd(t_parse *parse, t_list **my_env, t_exec *data, int *index)
{
	int	pipes[2];
	int	tmp;

	tmp = index[0];
	pipe(pipes);
	pipe(data->pipe);
	if (index[0] != 0)
		dup_inter_in(data);
	while (index[0] < index[1])
	{
		if (parse[index[0]].type == HEREDOC)
			data->current_fd_in = dup_in(parse, index[0], pipes, data);
		if (parse[index[0]].type == INFILE)
			data->current_fd_in = dup_in(parse, index[0], pipes, data);
		if (parse[index[0]].type == OUTFILE)
			data->current_fd_out = dup_out(parse, index[0]);
		index[0]++;
	}
	dup_inter_out(data, parse, index[1]);
	double_close(pipes[0], pipes[1]);
	piped_cmd_execution(parse, my_env, data, index[0]);
	// double_close(data->pipe[0], data->pipe[1]);
	// restore_dup(file, data, pipes[0]);
}

int	is_pipe_after(t_parse *parse, int index)
{
	while (parse[index].str)
	{
		if (parse[index].type == PIPEE)
			return (1);
		index++;
	}
	return (0);
}

int	how_many_pipes(t_parse *parse)
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
	return (count + 1);
}

void	piped_cmd_execution(t_parse *parse, t_list **my_env, t_exec *data, int runner)
{

	while (parse[runner].str)
	{
		if (parse[runner].type == COMMAND)
		{
			if (which_builtin(parse, runner) == 1)
				handle_single_builtin(parse, my_env, runner);
			else if (which_builtin(parse, runner) == 2)
				handle_forked_single_builtin(parse, my_env, runner);
			else
				exec_single_cmd(parse, my_env, runner, data);
		}
		runner++;
	}
}
