/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_expanded_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 06:19:34 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 06:20:02 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_expanded_errno(t_entry *entry, int *ind, char quote);
static void	fill_expanded_else(t_entry *entry, char *str, int *ind, char quote);
static void	add_var(t_entry *entry, char *str, int *j, char quote);
static void	set_context(t_entry *entry, int j, char quote);

void	fill_expanded_redir(t_entry *entry, char *str, t_list **my_env)
{
	int		ind[2];
	char	quote;

	ind[0] = 0;
	ind[1] = 0;
	quote = 0;
	while (str[ind[0]])
	{
		if (quote == 0 && (str[ind[0]] == '\'' || str[ind[0]] == '\"'))
			set_quote(&quote, str[ind[0]], &ind[0]);
		else if (quote == str[ind[0]])
			set_quote(&quote, 0, &ind[0]);
		else if (str[ind[0]] == '$' && is_env_var(&str[ind[0]], quote))
		{
			if (str[ind[0] + 1] == '?')
				fill_expanded_errno(entry, ind, quote);
			else
				add_var(entry, ft_getenv(my_env, \
						get_name_var(str, &ind[0]), 1), &ind[1], quote);
		}
		else
			fill_expanded_else(entry, str, ind, quote);
	}
	entry[ind[1]].c = 0;
}

static void	fill_expanded_errno(t_entry *entry, int *ind, char quote)
{
	add_var(entry, ft_itoa(g_errno), &ind[1], quote);
	ind[0] += 2;
}

static void	fill_expanded_else(t_entry *entry, char *str, int *ind, char quote)
{
	entry[ind[1]].c = str[ind[0]];
	entry[ind[1]].type = -1;
	set_context(entry, ind[1], quote);
	ind[0]++;
	ind[1]++;
}

static void	add_var(t_entry *entry, char *str, int *j, char quote)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		entry[*j].c = str[i];
		entry[*j].type = -1;
		set_context(entry, *j, quote);
		*j += 1;
		i++;
	}
	free(str);
}

static void	set_context(t_entry *entry, int j, char quote)
{
	if (quote == 0)
		entry[j].context = NO_QUOTE;
	else if (quote == '\'')
		entry[j].context = SI_QUOTE;
	else
		entry[j].context = DO_QUOTE;
}
