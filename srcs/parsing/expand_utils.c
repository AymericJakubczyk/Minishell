/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:55:11 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/26 04:40:25 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name_env(t_entry *entry, int *i)
{
	char	*env_name;

	env_name = ft_strdup("");
	*i += 1;
	if (entry[*i].c && ft_isdigit(entry[*i].c))
	{
		*i += 1;
		return (env_name);
	}
	while (ft_isalnum(entry[*i].c) || entry[*i].c == '_')
	{
		env_name = ft_strjoin2(env_name, char_to_str(entry[*i].c));
		*i += 1;
	}
	return (env_name);
}

void	copy_entry_value(t_entry *entry, t_entry *new_entry, int *i, int *j)
{
	new_entry[*j].c = entry[*i].c;
	new_entry[*j].type = entry[*i].type;
	new_entry[*j].context = entry[*i].context;
	*i += 1;
	*j += 1;
}

int	good_char_env(t_entry *entry, int i)
{
	if (entry[i + 1].c && (ft_isalnum(entry[i + 1].c) || \
		entry[i + 1].c == '_' || entry[i + 1].c == '?'))
		return (1);
	return (0);
}

int	check_tild(t_entry *entry, int i)
{
	if (i - 1 >= 0 && entry[i - 1].type == CHAR)
		return (0);
	if (entry[i + 1].c && entry[i + 1].type == CHAR && entry[i + 1].c != '/')
		return (0);
	return (1);
}

void	fill_value_env(t_entry *new_entry, \
		int context, char *value_env, int *j)
{
	int	i;

	i = 0;
	while (value_env && value_env[i])
	{
		new_entry[*j].c = value_env[i];
		if (new_entry[*j].c == ' ' || new_entry[*j].c == '\t')
			new_entry[*j].type = WHITESPACE;
		else
			new_entry[*j].type = EXPAND;
		new_entry[*j].context = context;
		*j += 1;
		i++;
	}
	free(value_env);
}
