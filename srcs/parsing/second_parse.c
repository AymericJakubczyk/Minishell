/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:55:37 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/27 19:41:26 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_str(t_entry *entry, int *i, int j);
static void	set_type(t_parse *parse, t_entry *entry);

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
	set_type(parse, entry);
	print_parse(parse);
	if (check_parse(parse) == -1)
		return (g_errno = 2, 0);
	return (1);
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
	if (!str)
		ft_error(ERROR_42, NULL);
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

// static void	set_type(t_parse *parse, t_entry *entry)
// {
// 	int	i;
// 	int	cmd;

// 	cmd = 0;
// 	i = 0;
// 	while (parse[i].str)
// 	{
// 		if (parse[i].str[0] == '<' && context_in_parse2(entry, parse, i) == NO_QUOTE && ft_strlen(parse[i].str) == 1)
// 			set_type_utils(REDIRECT_IN, INFILE, &i, parse);
// 		else if (parse[i].str[0] == '<' && context_in_parse2(entry, parse, i) == NO_QUOTE && ft_strlen(parse[i].str) == 2)
// 			set_type_utils(HEREDOC, LIMITER, &i, parse);
// 		else if (parse[i].str[0] == '>' && context_in_parse2(entry, parse, i) == NO_QUOTE && ft_strlen(parse[i].str) == 1)
// 			set_type_utils(REDIRECT_OUT, OUTFILE, &i, parse);
// 		else if (parse[i].str[0] == '>' && context_in_parse2(entry, parse, i) == NO_QUOTE && ft_strlen(parse[i].str) == 2)
// 			set_type_utils(APPEND, OUTFILE, &i, parse);
// 		else if (parse[i].str[0] == '|' && context_in_parse2(entry, parse, i) == NO_QUOTE)
// 			set_type_utils2(PIPEE, &cmd, &i, parse);
// 		else if (cmd == 0)
// 			set_type_utils2(COMMAND, &cmd, &i, parse);
// 		else
// 		{
// 			parse[i].type = CMD_ARG;
// 			i++;
// 		}	
// 	}
// }

static void	set_type(t_parse *parse, t_entry *entry)
{
	int	i;
	int	cmd;

	cmd = 0;
	i = 0;
	while (parse[i].str)
	{
		if (parse[i].str[0] == '<' && context_in_parse2(entry, parse, i) == NO_QUOTE && ft_strlen(parse[i].str) == 1)
			set_type_utils(REDIRECT_IN, &i, parse);
		else if (parse[i].str[0] == '<' && context_in_parse2(entry, parse, i) == NO_QUOTE && ft_strlen(parse[i].str) == 2)
			set_type_utils(HEREDOC, &i, parse);
		else if (parse[i].str[0] == '>' && context_in_parse2(entry, parse, i) == NO_QUOTE && ft_strlen(parse[i].str) == 1)
			set_type_utils(REDIRECT_OUT, &i, parse);
		else if (parse[i].str[0] == '>' && context_in_parse2(entry, parse, i) == NO_QUOTE && ft_strlen(parse[i].str) == 2)
			set_type_utils(APPEND, &i, parse);
		else if (parse[i].str[0] == '|' && context_in_parse2(entry, parse, i) == NO_QUOTE)
			set_type_utils2(PIPEE, &cmd, &i, parse);
		else if (cmd == 0)
			set_type_utils2(COMMAND, &cmd, &i, parse);
		else
		{
			if (i - 1 >= 0 && parse[i - 1].type == REDIRECT_IN)
				set_type_utils(INFILE, &i, parse);
			else if (i - 1 >= 0 && parse[i - 1].type == HEREDOC)
				set_type_utils(LIMITER, &i, parse);
			else if (i - 1 >= 0 && (parse[i - 1].type == REDIRECT_OUT || parse[i - 1].type == APPEND))
				set_type_utils(OUTFILE, &i, parse);
			else
				set_type_utils(CMD_ARG, &i, parse);
		}	
	}
}

int	context_in_parse2(t_entry *entry, t_parse *parse, int i)
{
	int	ind_parse;
	int	ind_entry;
	int	j;

	ind_parse = 0;
	ind_entry = 0;
	while (ind_parse < i)
	{
		j = 0;
		while (j < ft_strlen(parse[ind_parse].str))
		{
			j++;
			ind_entry++;
		}
		while (entry[ind_entry].type == WHITESPACE)
			ind_entry++;
		ind_parse++;
	}
	return (entry[ind_entry].context);
}
