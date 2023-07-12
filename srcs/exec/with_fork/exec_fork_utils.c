/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:34:47 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/12 17:34:48 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nbr_arg(t_parse *parse);
static void	fill_arg(t_parse *parse, char **arg);

int	last_redir(t_parse *parse, int mode)
{
	int	type_redirect;
	int	i;

	type_redirect = -1;
	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (mode == IN && (parse[i].type == REDIRECT_IN || parse[i].type == HEREDOC))
			type_redirect = parse[i].type;
		if (mode == OUT && (parse[i].type == REDIRECT_OUT || parse[i].type == APPEND))
			type_redirect = parse[i].type;
		i++;
	}
	return (type_redirect);
}

char *get_last_file(t_parse *parse, t_list **my_env, int mode)
{
	int i;

	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
		i++;
	while (i >= 0)
	{
		if (mode == IN && parse[i].type == INFILE)
			return (expand_redirect(parse[i], my_env));
		if (mode == OUT && parse[i].type == OUTFILE)
			return (expand_redirect(parse[i], my_env));
		i--;
	}
	return (NULL); //normalement il le fait jamais
}

char	**get_arg(t_parse *parse)
{
	char	**arg;
	int		size;

	size = get_nbr_arg(parse);
	//dprintf(2, "size of arg %d\n", size);
	arg = malloc(sizeof(char *) * (size + 1));
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
	int i;
	int num_arg;

	i = 0;
	num_arg = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == COMMAND)
		{
			arg[0] = parse[i].str;
			num_arg++;
		}
		i++;
	}
	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == CMD_ARG)
		{
			arg[num_arg] = parse[i].str;
			num_arg++;
		}
		i++;
	}
	arg[num_arg] = NULL;
}
