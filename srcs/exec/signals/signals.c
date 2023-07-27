/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 07:58:06 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/25 07:58:07 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_heredoc(int sig)
{
	(void) sig;
	g_errno = 130;
	close(0);
}

void	handler_fork(int sig)
{
	if (sig == SIGINT)
	{
		g_errno = 130;
		ft_dprintf("\n");
	}
	if (sig == SIGQUIT)
	{
		g_errno = 131;
		ft_dprintf("Quit (core dumped salaud)\n");
	}
}

void	handler_fork_slash(int sig)
{
	if (sig == SIGQUIT)
	{
		g_errno = 131;
		ft_dprintf("Quit (core dumped salaud)\n");
	}
}
