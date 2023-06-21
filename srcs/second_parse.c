/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:55:37 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/21 14:54:27 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_str(t_entry *entry, int *i, int j);
static void	set_type(t_parse *parse);

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
				return (free(entry), free_all_parse(parse), -1);
			nbr++;
		}
	}
	parse[nbr].str = NULL;
	if (check_parse(parse) == -1)
		return (0);
	return (set_type(parse), 1);
}

static char	*get_str(t_entry *entry, int *i, int j)
{
	char	*str;
	int		runner;

	runner = 0;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (runner < j)
	{
		str = ft_strjoin2(str, char_to_str(entry[*i].c));
		*i += 1;
		runner++;
	}
	return (str);
}

int	go_to_end_block(t_entry *entry)
{
	int	i;

	i = 0;
	if (entry[i].type == CHEV_IN && entry[i].context == NO_QUOTE)
	{
		i++;
		if (entry[i].type == CHEV_IN && entry[i].context == NO_QUOTE)
			return (2);
		return (i);
	}
	if (entry[i].type == CHEV_OUT && entry[i].context == NO_QUOTE)
	{
		i++;
		if (entry[i].type == CHEV_OUT && entry[i].context == NO_QUOTE)
			return (2);
		return (i);
	}
	while (entry[i].c != '\0' && !(entry[i].type == WHITESPACE && \
			entry[i].context == NO_QUOTE) && !(entry[i].context == \
			NO_QUOTE && (entry[i].type == CHEV_IN || entry[i].type == \
			CHEV_OUT || entry[i].type == PIPE)))
		i += 1;
	if (i == 0)
		return (1);
	return (i);
}

static void	set_type(t_parse *parse)
{
	int	i;
	int	cmd;

	cmd = 0;
	i = 0;
	while (parse[i].str)
	{
		if (parse[i].str[0] == '<' && ft_strlen(parse[i].str) == 1)
			set_type_utils(REDIRECT_IN, INFILE, &i, parse);
		else if (parse[i].str[0] == '<' && ft_strlen(parse[i].str) == 2)
			set_type_utils(HEREDOC, LIMITER, &i, parse);
		else if (parse[i].str[0] == '>' && ft_strlen(parse[i].str) == 1)
			set_type_utils(REDIRECT_OUT, OUTFILE, &i, parse);
		else if (parse[i].str[0] == '>' && ft_strlen(parse[i].str) == 2)
			set_type_utils(APPEND, OUTFILE, &i, parse);
		else if (parse[i].str[0] == '|')
			set_type_utils2(PIPEE, &cmd, &i, parse);
		else if (cmd == 0)
			set_type_utils2(COMMAND, &cmd, &i, parse);
		else
		{
			parse[i].type = CMD_ARG;
			i++;
		}	
	}
}
