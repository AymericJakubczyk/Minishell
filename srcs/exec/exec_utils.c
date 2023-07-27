/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:08:26 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/27 07:25:39 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_file(t_exec *data)
{
	data->current_fd_in = data->fd_in;
	data->current_fd_out = data->fd_out;
}

int	is_directory(char *cmd, t_list **env, t_exec *data)
{
	int	fd;

	if (access(cmd, F_OK) != 0)
	{
		ft_error(ERROR_13, cmd, 127);
		free_minishell(data, env);
		exit(g_errno);
	}
	if (access(cmd, X_OK) != 0 && ft_strlen(cmd) != 0)
	{
		ft_dprintf("%s\n", cmd);
		ft_error(ERROR_15, cmd, 126);
		free_minishell(data, env);
		exit(g_errno);
	}
	fd = open(cmd, O_DIRECTORY);
	if (fd != -1 && slash_in(cmd))
	{
		close (fd);
		ft_error(ERROR_24, cmd, 126);
		free_minishell(data, env);
		exit(g_errno);
	}
	return (0);
}

int	slash_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	find_arg(t_parse *parse)
{
	int	runner;
	int	index;

	index = 0;
	runner = 0;
	while (parse[runner].str)
	{
		if (parse[runner].type == CMD_ARG)
		{
			if (parse[runner].str[index] == '-')
			{
				while (parse[runner].str[index])
					index++;
				if (index == 2 && parse[runner].str[0] == '-' \
					&& parse[runner].str[1] == '-')
					return (0);
				if (index >= 2)
					return (ft_error(ERROR_25, parse[runner].str, 2), -1);
				index = 0;
			}
		}
		runner++;
	}
	return (0);
}
