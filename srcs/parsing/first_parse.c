/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:49:00 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/11 18:27:17 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	which_type(t_entry *entry, char c);
static void	which_context(t_entry *entry, char quote);

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

static void	which_type(t_entry *entry, char c)
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

static void	which_context(t_entry *entry, char quote)
{
	if (quote == 0)
		entry->context = NO_QUOTE;
	if (quote == '\'')
		entry->context = SI_QUOTE;
	if (quote == '\"')
		entry->context = DO_QUOTE;
}
