/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:55:37 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/09 14:01:37 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	which_context(t_entry *entry, char quote);
void	which_type(t_entry *entry, char c);

void	check_syntax_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == quote)
			quote = 0;
		else if (str[i] == '\'' && quote == 0)
			quote = '\'';
		else if (str[i] == '\"' && quote == 0)
			quote = '\"';
		i++;
	}
	if (quote != 0)
	{
		ft_printf("syntax error!\n");
		exit(2);
	}
	// else
		// ft_printf("good quote\n");
}

int	go_to_end_block(t_entry *entry)
{
	int	i;

	i = 0;
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

char	*char_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = 0;
	return (str);
}

char	*get_str(t_entry *entry, int *i, int j)
{
	char	*str;
	int		runner;

	runner = 0;
	str = ft_strdup("");
	while (runner < j)
	{
		str = ft_strjoin2(str, char_to_str(entry[*i].c));
		*i += 1;
		runner++;
	}
	return (str);
}

void	colapse_all(t_entry *entry, t_parse *parse)
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
			nbr++;
		}
	}
	parse[nbr].str = NULL;
}
