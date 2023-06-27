/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:24:05 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/27 19:42:56 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	dup_in()
// {
// 	int	empty_pipe[2];

// 	if (i == 0)
// 	{
// 		if (dup2(file[0], STDIN_FILENO) == -1)
// 			free_and_exit(all_cmd, 1);
// 	}
// 	else if (prec_fd != 0)
// 	{
// 		if (dup2(prec_fd, STDIN_FILENO) == -1)
// 			free_and_exit(all_cmd, 1);
// 	}
// 	else
// 	{
// 		pipe(empty_pipe);
// 		if (dup2(empty_pipe[0], STDIN_FILENO) == -1)
// 		{
// 			double_close(empty_pipe[0], empty_pipe[1]);
// 			free_and_exit(all_cmd, 1);
// 		}
// 		double_close(empty_pipe[0], empty_pipe[1]);
// 	}
// }

// void	dup_out()
// {
// 		if (dup2(my_struct.file[1], STDOUT_FILENO) == -1)
// 			free_and_exit(all_cmd, 1);
// 	else
// 	{
// 		if (dup2(my_struct.pipes1[1], STDOUT_FILENO) == -1)
// 			free_and_exit(all_cmd, 1);
// 	}
// }
