/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:34:24 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/24 20:13:18 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_with_env_value(t_entry *entry, t_entry *new_entry, \
	t_list **my_env, int *ind);
static void	fill_with_tild_value(t_entry *entry, t_entry *new_entry, int *ind, \
	t_list **my_env);
static void	keep_redirection(t_entry *entry, t_entry *new_entry, int *i, \
	int *j);
static void	else_fill_new_entry(t_entry *entry, t_entry *new_entry, int *ind, t_list **my_env);
void	print_or_not(t_entry *entry, t_entry *new_entry, int *ind);
int		void_var(t_entry *entry, int *ind, t_list **my_env);

int	fill_expand(t_entry *entry, t_entry *new_entry, t_list **my_env)
{
	int		ind[2];

	ind[0] = 0;
	ind[1] = 0;
	while (entry[ind[0]].c)
	{
		if (entry[ind[0]].c == '$' && entry[ind[0]].context != SI_QUOTE)
		{
			if (!good_char_env(entry,ind[0]))
				print_or_not(entry, new_entry, ind);
			else if (fill_with_env_value(entry, new_entry, my_env, ind) == -1)
				return (-1);
		}
		else if (entry[ind[0]].c == '~' && entry[ind[0]].context != SI_QUOTE \
			&& check_tild(entry, ind[0]))
			fill_with_tild_value(entry, new_entry, ind, my_env);
		else if ((entry[ind[0]].type == CHEV_IN || \
			entry[ind[0]].type == CHEV_OUT) && entry[ind[0]].context == 0)
			keep_redirection(entry, new_entry, &ind[0], &ind[1]);
		else
			else_fill_new_entry(entry, new_entry, ind, my_env);
	}
	new_entry[ind[1]].c = 0;
	return (0);
}

static int	fill_with_env_value(t_entry *entry, t_entry *new_entry, \
	t_list **my_env, int *ind)
{
	int		context;
	char	*name_env;

	if (entry[ind[0] + 1].c && entry[ind[0] + 1].c == '?')
	{
		fill_value_env(new_entry, entry[ind[0]].context, ft_itoa(g_errno), \
			&ind[1]);
		ind[0] += 2;
	}
	else
	{
		context = entry[ind[0]].context;
		name_env = get_name_env(entry, &ind[0]);
		if (!name_env)
		{
			ft_error(ERROR_42, NULL, 12);
			return (-1);
		}
		fill_value_env(new_entry, context, ft_getenv(my_env, name_env, 1), \
			&ind[1]);
	}
	return (0);
}

static void	fill_with_tild_value(t_entry *entry, t_entry *new_entry, int *ind, \
	t_list **my_env)
{
	char	*value_env;

	value_env = ft_getenv(my_env, "HOME", 0);
	fill_value_env(new_entry, entry[ind[0]].context, value_env, &ind[1]);
	ind[0]++;
}
//free(value_env);

static void	keep_redirection(t_entry *entry, t_entry *new_entry, int *i, int *j)
{
	char	chev;
	int		size;

	chev = entry[*i].c;
	copy_entry_value(entry, new_entry, i, j);
	while (entry[*i].c == chev)
		copy_entry_value(entry, new_entry, i, j);
	while (entry[*i].c && entry[*i].type == WHITESPACE)
		copy_entry_value(entry, new_entry, i, j);
	size = go_to_end_block(&entry[*i]);
	while (entry[*i].c && size > 0)
	{
		copy_entry_value(entry, new_entry, i, j);
		size--;
	}
}

static void	else_fill_new_entry(t_entry *entry, t_entry *new_entry, int *ind, t_list **my_env)
{
	int	quote;

	if (entry[ind[0]].context == 0 && \
		(entry[ind[0]].type == S_QUOTE || entry[ind[0]].type == D_QUOTE))
	{
		quote = entry[ind[0]].type;
		if (is_void(entry, &ind[0], my_env))
		{
			new_entry[ind[1]].c = ' ';
			new_entry[ind[1]].type = VOID;
			new_entry[ind[1]].context = 0;
			ind[1] += 1;
		}
		else
			ind[0]++;
	}
	else
		copy_entry_value(entry, new_entry, &ind[0], &ind[1]);
}
//120 : ind[0] += 2;

int	is_void(t_entry *entry, int *ind, t_list **my_env)
{
	int	stock_ind;

	stock_ind = ind[0];
	if (ind[0] - 1 < 0 || (entry[ind[0] - 1].type == WHITESPACE && entry[ind[0] - 1].context == NO_QUOTE))
	{
		while (entry[stock_ind].c && ((entry[stock_ind].c == '$' && entry[stock_ind].context != SI_QUOTE) || ((entry[stock_ind].type == S_QUOTE || entry[stock_ind].type == D_QUOTE) && entry[stock_ind].context == NO_QUOTE)))
		{
			if (entry[stock_ind].c == '$' && entry[stock_ind].context == SI_QUOTE)
				return (0);
			if (entry[stock_ind].c == '$' && !good_char_env(entry, stock_ind))
				return (0);
			if (entry[stock_ind].c == '$' && !void_var(entry, &stock_ind, my_env))
				return (0);
			stock_ind++;
		}
		if (!entry[stock_ind].c || (entry[stock_ind].type == WHITESPACE && entry[stock_ind].context == NO_QUOTE))
			return (*ind = stock_ind, 1);
	}
		return (0);
}

int	void_var(t_entry *entry, int *ind, t_list **my_env)
{
	int stock_ind;
	char *value_env;

	stock_ind = *ind;
	value_env = ft_getenv(my_env, get_name_env(entry, &stock_ind), 1);
	if (!value_env)
		return (*ind = stock_ind, 1);
	free(value_env);
	return (0);
}

void	print_or_not(t_entry *entry, t_entry *new_entry, int *ind)
{
	if ((entry[ind[0] + 1].c != '\'' && entry[ind[0] + 1].c != '\"') || entry[ind[0]].context == DO_QUOTE)
		else_fill_new_entry(entry, new_entry, ind, NULL);
	else
		ind[0]++;
}