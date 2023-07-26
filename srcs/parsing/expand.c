/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:13:46 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/26 04:42:38 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_entry *entry, t_entry **new_entry, t_list **my_env)
{
	int	size;

	size = get_expand_size(entry, my_env);
	if (size == -1)
		return ;
	*new_entry = malloc(sizeof(t_entry) * (size + 1));
	if (!new_entry)
	{
		ft_error(ERROR_42, NULL, 12);
		return ;
	}
	fill_expand(entry, *new_entry, my_env);
}

int	is_void(t_entry *entry, int *ind, t_list **my_env)
{
	int	stock_ind;

	stock_ind = ind[0];
	if (ind[0] - 1 < 0 || good_border_of_void(entry[ind[0] - 1]))
	{
		while (entry[stock_ind].c && ((entry[stock_ind].c == '$' && \
			entry[stock_ind].context != SI_QUOTE) || ((entry[stock_ind].type \
			== S_QUOTE || entry[stock_ind].type == D_QUOTE) && \
			entry[stock_ind].context == NO_QUOTE)))
		{
			if (entry[stock_ind].c == '$' && \
				entry[stock_ind].context == SI_QUOTE)
				return (0);
			if (entry[stock_ind].c == '$' && !good_char_env(entry, stock_ind))
				return (0);
			if (entry[stock_ind].c == '$' && \
				!void_var(entry, &stock_ind, my_env))
				return (0);
			stock_ind++;
		}
		if (!entry[stock_ind].c || good_border_of_void(entry[stock_ind]))
			return (*ind = stock_ind, 1);
	}
	return (0);
}

int	good_border_of_void(t_entry entry)
{
	if (entry.type != CHAR && entry.type != S_QUOTE && entry.type != D_QUOTE \
		&& entry.context == NO_QUOTE)
		return (1);
	return (0);
}

int	void_var(t_entry *entry, int *ind, t_list **my_env)
{
	int		stock_ind;
	char	*value_env;

	stock_ind = *ind;
	value_env = ft_getenv(my_env, get_name_env(entry, &stock_ind), 1);
	if (!value_env)
		return (*ind = stock_ind, 1);
	free(value_env);
	return (0);
}

void	print_or_not(t_entry *entry, t_entry *new_entry, int *ind)
{
	if ((entry[ind[0] + 1].c != '\'' && entry[ind[0] + 1].c != '\"') || \
		entry[ind[0]].context == DO_QUOTE)
		else_fill_new_entry(entry, new_entry, ind, NULL);
	else
		ind[0]++;
}
