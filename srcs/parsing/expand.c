/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:13:46 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/25 20:47:53 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_new_size(t_entry *entry, t_list **my_env);
char	*get_name_env(t_entry *entry, int *i);
int		fill_new_entry(t_entry *entry, t_entry *new_entry, t_list **my_env);
void	fill_value_env(t_entry *new_entry, int context, char *value_env, int *j);
int		check_tild(t_entry *entry, int i);
void	keep_redirection(t_entry *entry, t_entry *new_entry, int *i, int *j);
void	copy_entry_value(t_entry *entry, t_entry *new_entry, int *i, int *j);
void	inc_size_after_chev(t_entry *entry, int *i, int *size);
void	inc_size_of_tild_value(t_list **my_env, int *i, int *size);
int		fill_with_env_value(t_entry *entry, t_entry *new_entry, t_list **my_env, int *ind);
void	else_fill_new_entry(t_entry *entry, t_entry *new_entry, int *ind);
void	fill_with_tild_value(t_entry *entry, t_entry *new_entry, int *ind, t_list **my_env);
void 	ft_increment(int *i, int *size);

void	expand(t_entry *entry, t_entry **new_entry, t_list **my_env)
{
	int	size;

	size = get_new_size(entry, my_env);
	if (size == -1)
		return ;
	*new_entry = malloc(sizeof(t_entry) * (size + 1));
	if (!new_entry)
	{
		ft_error(ERROR_42, NULL);
		return ;
	}
	fill_new_entry(entry, *new_entry, my_env);
}

int	get_new_size(t_entry *entry, t_list **my_env)
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
			ft_increment(&i, &size);
	}
	return (size);
}

void	ft_increment(int *i, int *size)
{
	*i += 1;
	*size += 1;
}

void	inc_size_after_chev(t_entry *entry, int *i, int *size)
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

void	inc_size_of_tild_value(t_list **my_env, int *i, int *size)
{
	char	*value_env;

	value_env = ft_getenv(my_env, "HOME", 0);
	*size += ft_strlen(value_env);
	free(value_env);
	*i += 1;
}

int	inc_size_of_var_value(t_list **my_env, t_entry *entry, int *i, int *size)
{
	char	*value_env;
	char	*name_env;

	if (entry[*i + 1].c && entry[*i + 1].c == '?')
	{
		*size += ft_strlen(ft_itoa(g_errno));
		*i += 2;
	}
	else
	{
		name_env = get_name_env(entry, i);
		if (!name_env)
		{
			ft_error(ERROR_42, NULL);
			g_errno = 12;
			return (-1);
		}
		value_env = ft_getenv(my_env, name_env, 1);
		*size += ft_strlen(value_env);
		free(value_env);
	}
	return (0);
}

char	*get_name_env(t_entry *entry, int *i)
{
	char	*env_name;

	env_name = ft_strdup("");
	*i += 1;
	while (ft_isalnum(entry[*i].c) || entry[*i].c == '_')
	{
		env_name = ft_strjoin2(env_name, char_to_str(entry[*i].c));
		*i += 1;
	}
	return (env_name);
}

int	fill_new_entry(t_entry *entry, t_entry *new_entry, t_list **my_env)
{
	int		ind[2];

	ind[0] = 0;
	ind[1] = 0;
	while (entry[ind[0]].c)
	{
		if (entry[ind[0]].c == '$' && entry[ind[0]].context != SI_QUOTE \
			&& good_char_env(entry, ind[0]))
		{
			if (fill_with_env_value(entry, new_entry, my_env, ind) == -1)
				return (-1);
		}
		else if (entry[ind[0]].c == '~' && entry[ind[0]].context != SI_QUOTE \
			&& check_tild(entry, ind[0]))
			fill_with_tild_value(entry, new_entry, ind, my_env);
		else if ((entry[ind[0]].type == CHEV_IN || \
			entry[ind[0]].type == CHEV_OUT) && entry[ind[0]].context == 0)
			keep_redirection(entry, new_entry, &ind[0], &ind[1]);
		else
			else_fill_new_entry(entry, new_entry, ind);
	}
	new_entry[ind[1]].c = 0;
	return (0);
}

void	fill_with_tild_value(t_entry *entry, t_entry *new_entry, int *ind, t_list **my_env)
{
	char *value_env;

	value_env = ft_getenv(my_env, "HOME", 0);
	fill_value_env(new_entry, entry[ind[0]].context, value_env, &ind[1]);
	free(value_env);
	ind[0]++;
}

void	else_fill_new_entry(t_entry *entry, t_entry *new_entry, int *ind)
{
	if (entry[ind[0]].context == 0 && \
		(entry[ind[0]].type == S_QUOTE || entry[ind[0]].type == D_QUOTE))
		ind[0]++;
	else
		copy_entry_value(entry, new_entry, &ind[0], &ind[1]);
}

int	fill_with_env_value(t_entry *entry, t_entry *new_entry, t_list **my_env, int *ind)
{
	int		context;
	char	*name_env;

	if (entry[ind[0] + 1].c && entry[ind[0] + 1].c == '?')
	{
		ft_printf("errno value : %s\n", ft_itoa(g_errno));
		fill_value_env(new_entry, entry[ind[0]].context, ft_itoa(g_errno), &ind[1]);
		ind[0] += 2;
	}
	else
	{
		context = entry[ind[0]].context;
		name_env = get_name_env(entry, &ind[0]);
		if (!name_env)
		{
			ft_error(ERROR_42, NULL);
			g_errno = 12;
			return (-1);
		}
		fill_value_env(new_entry, context, ft_getenv(my_env, name_env, 1), &ind[1]);
	}
	return (0);
}

void	keep_redirection(t_entry *entry, t_entry *new_entry, int *i, int *j)
{
	char	chev;
	int		size;

	chev = entry[*i].c;
	copy_entry_value(entry, new_entry, i, j);
	while (entry[*i].c == chev)
		copy_entry_value(entry, new_entry, i, j);
	while (entry[*i].c && entry[*i].type == WHITESPACE)
		*i += 1;
	size = go_to_end_block(&entry[*i]);
	while (entry[*i].c && size > 0)
	{
		copy_entry_value(entry, new_entry, i, j);
		size--;
	}
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

void	fill_value_env(t_entry *new_entry, int context, char *value_env, int *j)
{
	int	i;

	i = 0;
	//ft_printf("value env : %s context : %d\n", value_env, context);
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
