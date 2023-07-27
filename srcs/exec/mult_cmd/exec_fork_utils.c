/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:34:47 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 07:35:01 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nbr_arg(t_parse *parse);
static int	fill_arg(t_parse *parse, char **arg);
static int	fill_cmd_arg(t_parse *parse, char **arg);
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
		return (ft_error(ERROR_42, NULL, 1), NULL);
	if (fill_arg(parse, arg) == -1)
		return (ft_error(ERROR_42, NULL, 1), NULL);
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

static int	fill_arg(t_parse *parse, char **arg)
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
			if (!arg[0])
			{
				free(arg);
				return (-1);
			}
			num_arg++;
		}
		i++;
	}
	if (fill_cmd_arg(parse, arg) == -1)
		return (-1);
	return (0);
}

static int	fill_cmd_arg(t_parse *parse, char **arg)
{
	int	i;
	int	num_arg;

	num_arg = 1;
	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == CMD_ARG)
		{
			arg[num_arg] = ft_strdup(parse[i].str);
			if (!arg[num_arg])
			{
				free_all_tab(arg, num_arg);	
				return (-1);
			}
			num_arg++;
		}
		i++;
	}
	arg[num_arg] = NULL;
	return (0);
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

