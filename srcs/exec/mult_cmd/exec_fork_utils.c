/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:34:47 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/26 06:02:11 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nbr_arg(t_parse *parse);
static void	fill_arg(t_parse *parse, char **arg);
int			get_start_cmd(t_parse *parse, int num_cmd);

char	**get_arg(t_parse *parse)
{
	char	**arg;
	int		size;

	size = get_nbr_arg(parse);
	if (size == 0)
		return (NULL);
	arg = malloc(sizeof(char *) * (size + 1));
	if (!arg)
		return (ft_error(ERROR_42, NULL, 2), NULL);
	fill_arg(parse, arg);
	return (arg);
}

static int	get_nbr_arg(t_parse *parse)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == COMMAND || parse[i].type == CMD_ARG)
			nbr++;
		i++;
	}
	return (nbr);
}

static void	fill_arg(t_parse *parse, char **arg)
{
	int	i;
	int	num_arg;

	i = 0;
	num_arg = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == COMMAND)
		{
			arg[0] = ft_strdup(parse[i].str);
			num_arg++;
		}
		i++;
	}
	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == CMD_ARG)
		{
			arg[num_arg] = ft_strdup(parse[i].str);
			num_arg++;
		}
		i++;
	}
	arg[num_arg] = NULL;
}

int	get_start_cmd(t_parse *parse, int num_cmd)
{
	int	start;
	int	n_cmd;

	start = 0;
	n_cmd = 0;
	while (n_cmd < num_cmd && parse[start].str)
	{
		if (parse[start].type == PIPEE)
			n_cmd++;
		start++;
	}
	return (start);
}
