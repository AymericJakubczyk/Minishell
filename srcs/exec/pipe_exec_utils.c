/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:39:58 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/30 19:26:33 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_inter_in(t_exec *data)
{
	if (dup2(data->pipe[0], STDIN_FILENO))
		ft_printf("inter dup in failed\n");
}

void	dup_inter_out(t_exec *data, t_parse *parse, int index)
{
	if (parse[index].type != PIPEE)
	{
		if (dup2(data->pipe[1], STDOUT_FILENO))
			ft_printf("inter dup out failed\n");
	}
	else
	{
		ft_printf("%d\n", data->pipe[1]);
		if (dup2(data->pipe[1], STDOUT_FILENO))
			ft_printf("out failed\n");
	}
}
