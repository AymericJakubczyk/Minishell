/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:05:40 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/18 11:33:51 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_parse *parse, t_list **my_env, int runner);

//return 2 if fork is needed
int	which_builtin(t_parse *parse, int runner)
{
	if (ft_strcmp(parse[runner].str, "echo") == 0)
		return (2);
	if (ft_strcmp(parse[runner].str, "env") == 0)
		return (2);
	if (ft_strcmp(parse[runner].str, "pwd") == 0)
		return (2);
	if (ft_strcmp(parse[runner].str, "export") == 0)
	{
		if (parse[runner + 1].type == CMD_ARG)
			return (1);
		else
			return (2);
	}
	if (ft_strcmp(parse[runner].str, "exit") == 0)
		return (1);
	if (ft_strcmp(parse[runner].str, "unset") == 0)
		return (1);
	if (ft_strcmp(parse[runner].str, "cd") == 0)
		return (1);
	return (0);
}
