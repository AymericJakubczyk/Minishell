/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 06:19:43 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 06:20:28 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_expanded_redir(t_entry *entry);
static char	*colapse_entry(t_entry *entry);
static int	get_ind_last_char(t_entry *entry);

char	*expand_redirect(t_parse parse, t_list **my_env)
{
	t_entry	*entry;
	char	*expanded;

	expanded = NULL;
	entry = malloc(sizeof(t_entry) * \
	(size_expanded_redir(parse.str, my_env) + 1));
	if (!entry)
	{
		return (ft_error(ERROR_42, NULL, 1), NULL);
	}
	fill_expanded_redir(entry, parse.str, my_env);
	if (!check_expanded_redir(entry))
		return (NULL);
	expanded = colapse_entry(entry);
	free(entry);
	return (expanded);
}

int	check_expanded_redir(t_entry *entry)
{
	int	i;
	int	last_ind_char;

	i = 0;
	last_ind_char = get_ind_last_char(entry);
	while (entry[i].c && (entry[i].c == ' ' || \
	entry[i].c == '\t') && entry[i].context == NO_QUOTE)
		i++;
	if (!entry[i].c)
		return (ft_dprintf("AMBIGUOUS REDIRECTION !\n"), 0);
	while (entry[i].c && i <= last_ind_char)
	{
		if ((entry[i].c == ' ' || entry[i].c == '\t') \
		&& entry[i].context == NO_QUOTE)
			return (ft_dprintf("AMBIGUOUS REDIRECTION !\n"), 0);
		i++;
	}
	return (1);
}

static char	*colapse_entry(t_entry *entry)
{
	int		i;
	char	*expanded;
	int		last_ind_char;

	i = 0;
	last_ind_char = get_ind_last_char(entry);
	expanded = ft_strdup("");
	while (entry[i].c && (entry[i].c == ' ' || entry[i].c == '\t') \
	&& entry[i].context == NO_QUOTE)
		i++;
	while (entry[i].c && i <= last_ind_char)
	{
		expanded = ft_strjoin2(expanded, char_to_str(entry[i].c));
		i++;
	}
	return (expanded);
}

static int	get_ind_last_char(t_entry *entry)
{
	int	i;

	i = 0;
	while (entry[i].c)
		i++;
	i--;
	while (i >= 0 && (entry[i].c == ' ' || entry[i].c == '\t') \
	&& entry[i].context == NO_QUOTE)
		i--;
	return (i);
}
