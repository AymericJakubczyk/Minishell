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

void	single_cmd_execution(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	runner;

	runner = 0;
	while (parse[runner].str)
	{
		if (parse[runner].type == COMMAND)
		{
			if (which_builtin(parse, runner) == 1)
				handle_single_builtin(parse, my_env, runner, data);
			else if (which_builtin(parse, runner) == 2)
				handle_forked_single_builtin(parse, my_env, runner, data);
			else
				exec_single_cmd(parse, my_env, runner, data);
		}
		runner++;
	}
}
