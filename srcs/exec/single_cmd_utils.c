/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:24:05 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/29 11:11:09 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_in(t_parse *parse, int runner, int mode, int *pipe, t_exec *data)
{
	int		infile;
	char	*string;

	infile = 0;
	if (mode == 0)
	{
		infile = open(parse[runner].str, O_RDONLY);
		if (dup2(infile, STDIN_FILENO) == -1)
			ft_printf("Dup2 problem\n");
	}
	if (mode == 1)
	{
		string = ft_get_str_hd(parse, data, 1);
		write(pipe[1], string, ft_strlen(string));
		close(pipe[1]);
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			ft_printf("Dup2 problem\n");
	}
	if (!infile && !pipe[0])
		ft_printf("Open file error\n");
	return (infile);
}

int	dup_out(t_parse *parse, int runner)
{
	int	outfile;

	outfile = open(parse[runner].str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!outfile)
		ft_printf("Open file error");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		ft_printf("Dup2 problem\n");
	return (outfile);
}

void	double_close(int file1, int file2)
{
	if (file1)
		close(file1);
	if (file2)
		close(file2);
}

void	restore_dup(int file[2], t_exec *data, int *pipe)
{
	if (file[0] && file[0] != data->fd_in)
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			ft_printf("Dup2 failed to restore");
	if (pipe && pipe != data->fd_in)
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			ft_printf("Dup2 failed to restore");
	if (file[1] != data->fd_out)
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			ft_printf("Dup2 failed to restore");
}

void	single_cmd_execution(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	runner;

	runner = 0;
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
