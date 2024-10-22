/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:55:37 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 04:32:42 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_str(t_entry *entry, int *i, int j);
static void	set_type(t_parse *parse, t_entry *entry);
static void	next_set_type(t_parse *parse, int *i, int *cmd);
static int	context_in_parse(t_entry *entry, t_parse *parse, int i);

int	colapse_all(t_entry *entry, t_parse *parse)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (entry[i].c != '\0')
	{
		if (entry[i].type == WHITESPACE && entry[i].context == NO_QUOTE)
		{
			while (entry[i].c != '\0' && entry[i].type == WHITESPACE && \
					entry[i].context == NO_QUOTE)
				i++;
		}
		else
		{
			parse[nbr].str = get_str(entry, &i, go_to_end_block(&entry[i]));
			if (!parse[nbr].str)
				return (0);
			nbr++;
		}
	}
	parse[nbr].str = NULL;
	parse[nbr].type = -1;
	set_type(parse, entry);
	return (1);
}

static char	*get_str(t_entry *entry, int *i, int j)
{
	char	*str;
	int		runner;

	runner = 0;
	if (entry[*i].type == VOID)
	{
		*i += 1;
		return (char_to_str(0));
	}
	str = ft_strdup("");
	if (!str)
		return (ft_error(ERROR_42, NULL, 1), NULL);
	while (runner < j)
	{
		str = ft_strjoin2(str, char_to_str(entry[*i].c));
		*i += 1;
		runner++;
	}
	if (!str)
		ft_error(ERROR_42, NULL, 12);
	return (str);
}

static void	set_type(t_parse *parse, t_entry *entry)
{
	int	i;
	int	cmd;

	cmd = 0;
	i = 0;
	while (parse[i].str)
	{
		if (parse[i].str[0] == '<' && context_in_parse(entry, parse, i) \
			== NO_QUOTE && ft_strlen(parse[i].str) == 1)
			set_type_utils(REDIRECT_IN, &i, parse);
		else if (parse[i].str[0] == '<' && context_in_parse(entry, parse, i) \
			== NO_QUOTE && ft_strlen(parse[i].str) == 2)
			set_type_utils(HEREDOC, &i, parse);
		else if (parse[i].str[0] == '>' && context_in_parse(entry, parse, i) \
			== NO_QUOTE && ft_strlen(parse[i].str) == 1)
			set_type_utils(REDIRECT_OUT, &i, parse);
		else if (parse[i].str[0] == '>' && context_in_parse(entry, parse, i) \
			== NO_QUOTE && ft_strlen(parse[i].str) == 2)
			set_type_utils(APPEND, &i, parse);
		else if (parse[i].str[0] == '|' && context_in_parse(entry, parse, i) \
			== NO_QUOTE)
			set_type_utils2(PIPEE, &cmd, &i, parse);
		else
			next_set_type(parse, &i, &cmd);
	}
}

static void	next_set_type(t_parse *parse, int *i, int *cmd)
{
	if (*i - 1 >= 0 && parse[*i - 1].type == REDIRECT_IN)
		set_type_utils(INFILE, i, parse);
	else if (*i - 1 >= 0 && parse[*i - 1].type == HEREDOC)
		set_type_utils(LIMITER, i, parse);
	else if (*i - 1 >= 0 && (parse[*i - 1].type == REDIRECT_OUT || \
		parse[*i - 1].type == APPEND))
		set_type_utils(OUTFILE, i, parse);
	else if (*cmd == 0)
		set_type_utils2(COMMAND, cmd, i, parse);
	else
		set_type_utils(CMD_ARG, i, parse);
}

static int	context_in_parse(t_entry *entry, t_parse *parse, int i)
{
	int		ind_parse;
	int		ind_entry;
	size_t	j;

	ind_parse = 0;
	ind_entry = 0;
	while (ind_parse < i)
	{
		j = 0;
		if (ft_strlen(parse[ind_parse].str) == 0)
			ind_entry++;
		while (j < ft_strlen(parse[ind_parse].str))
		{
			j++;
			ind_entry++;
		}
		while (entry[ind_entry].type == WHITESPACE && \
			entry[ind_entry].context == NO_QUOTE)
			ind_entry++;
		ind_parse++;
	}
	if (entry[ind_entry].type == EXPAND)
		return (SI_QUOTE);
	return (entry[ind_entry].context);
}
