/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expand_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:30:16 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/26 04:42:56 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inc_size_after_chev(t_entry *entry, int *i, int *size);
static void	inc_size_of_tild_value(t_list **my_env, int *i, int *size);
static int	inc_size_of_var_value(t_list **my_env, t_entry *entry, int *i, \
	int *size);
static void	ft_increment(t_entry *entry, int *i, int *size, t_list **my_env);

int	get_expand_size(t_entry *entry, t_list **my_env)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (entry[i].c)
	{
		if ((entry[i].type == CHEV_IN || entry[i].type == CHEV_OUT) \
			&& entry[i].context == 0)
			inc_size_after_chev(entry, &i, &size);
		else if (entry[i].c == '~' && entry[i].context != SI_QUOTE \
			&& check_tild(entry, i))
			inc_size_of_tild_value(my_env, &i, &size);
		else if (entry[i].c == '$' && entry[i].context != SI_QUOTE \
			&& good_char_env(entry, i))
		{
			if (inc_size_of_var_value(my_env, entry, &i, &size) == -1)
				return (-1);
		}
		else
			ft_increment(entry, &i, &size, my_env);
	}
	return (size);
}

static void	inc_size_after_chev(t_entry *entry, int *i, int *size)
{
	int	type;

	type = entry[*i].type;
	while (type == entry[*i].type)
	{
		*i += 1;
		*size += 1;
	}
	while (entry[*i].c && entry[*i].type == WHITESPACE)
	{
		*i += 1;
		*size += 1;
	}
	*size += go_to_end_block(&entry[*i]);
	*i += go_to_end_block(&entry[*i]);
}

static void	inc_size_of_tild_value(t_list **my_env, int *i, int *size)
{
	char	*value_env;

	value_env = ft_getenv(my_env, "HOME", 0);
	*size += ft_strlen(value_env);
	free(value_env);
	*i += 1;
}

static int	inc_size_of_var_value(t_list **my_env, t_entry *entry, int *i, \
	int *size)
{
	char	*value_env;
	char	*name_env;
	char	*itoa;

	if (entry[*i + 1].c && entry[*i + 1].c == '?')
	{
		itoa = ft_itoa(g_errno);
		*size += ft_strlen(itoa);
		free(itoa);
		*i += 2;
	}
	else
	{
		name_env = get_name_env(entry, i);
		if (!name_env)
		{
			ft_error(ERROR_42, NULL, 12);
			g_errno = 12;
			return (-1);
		}
		value_env = ft_getenv(my_env, name_env, 1);
		*size += ft_strlen(value_env);
		free(value_env);
	}
	return (0);
}

static void	ft_increment(t_entry *entry, int *i, int *size, t_list **my_env)
{
	char	quote;

	if (entry[*i].context == NO_QUOTE && \
		(entry[*i].c == '\'' || entry[*i].c == '\"'))
	{
		quote = entry[*i].type;
		if (entry[*i + 1].c && entry[*i + 1].type == quote && \
			is_void(entry, i, my_env))
		{
			*size += 1;
		}
		else
			*i += 1;
	}
	else
	{
		*i += 1;
		*size += 1;
	}
}
