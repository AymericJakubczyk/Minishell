/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:55:37 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/11 15:49:05 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	which_context(t_entry *entry, char quote);
void	which_type(t_entry *entry, char c);
int		size_of_parse(t_entry *entry);

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

int	size_of_parse(t_entry *entry)
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
			nbr++;
			i += go_to_end_block(&entry[i]);
		}
	}
	return (nbr);
}

void	init_entry(t_entry *entry, char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		entry[i].c = str[i];
		which_type(&entry[i], str[i]);
		which_context(&entry[i], quote);
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == quote)
		{
			quote = 0;
			which_context(&entry[i], quote);
		}
		i++;
	}
	entry[i].c = '\0';
}

void	which_context(t_entry *entry, char quote)
{
	if (quote == 0)
		entry->context = NO_QUOTE;
	if (quote == '\'')
		entry->context = SI_QUOTE;
	if (quote == '\"')
		entry->context = DO_QUOTE;
}

void	which_type(t_entry *entry, char c)
{
	if (c == ' ' || c == '\t')
		entry->type = WHITESPACE;
	else if (c == '<')
		entry->type = CHEV_IN;
	else if (c == '>')
		entry->type = CHEV_OUT;
	else if (c == '|')
		entry->type = PIPE;
	else if (c == '\'')
		entry->type = S_QUOTE;
	else if (c == '\"')
		entry->type = D_QUOTE;
	else
		entry->type = CHAR;
}

