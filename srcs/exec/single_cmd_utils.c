/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:24:05 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/28 10:56:06 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_in(t_parse *parse, int runner)
{
	int	empty_pipe[2];
	int	infile;

	infile = open(parse[runner].str, O_RDONLY);
	if (!infile)
		ft_printf("Open file error\n");
	if (dup2(infile, STDIN_FILENO) == -1)
		ft_printf("Dup2 problem\n");
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

void	dup_out(t_parse *parse, int runner)
{
	int	outfile;

	outfile = open(parse[runner].str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!outfile)
		ft_printf("Open file error");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		ft_printf("Dup2 problem\n");
}
