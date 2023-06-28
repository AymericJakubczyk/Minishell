/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:24:05 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/28 19:08:40 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_in(t_parse *parse, int runner)
{
	int	infile;

	infile = open(parse[runner].str, O_RDONLY);
	if (!infile)
		ft_printf("Open file error\n");
	if (dup2(infile, STDIN_FILENO) == -1)
		ft_printf("Dup2 problem\n");
	return (infile);
	// else
	// {
	// 	pipe(empty_pipe);
	// 	if (dup2(empty_pipe[0], STDIN_FILENO) == -1)
	// 	{
	// 		double_close(empty_pipe[0], empty_pipe[1]);
	// 		free_and_exit(all_cmd, 1);
	// 	}
	// 	double_close(empty_pipe[0], empty_pipe[1]);
	// }
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

void	restore_dup(int file[2], t_exec *data)
{
	// ft_printf("%d, %d\n", file[0], data->fd_in);
	if (file[0] != data->fd_in)
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			ft_printf("Dup2 failed to restore");
	// ft_printf("%d, %d\n", file[1], data->fd_out);
	if (file[1] != data->fd_out)
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			ft_printf("Dup2 failed to restore");
}
