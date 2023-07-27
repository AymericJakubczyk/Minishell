/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:24:05 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/22 20:01:29 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_close(int *file1, int *file2)
{
	if (*file1 != -1)
	{
		close(*file1);
		*file1 = -1;
	}
	if (*file2 != -1)
	{
		close(*file2);
		*file2 = -1;
	}
}

void	verif_status(int status)
{
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
