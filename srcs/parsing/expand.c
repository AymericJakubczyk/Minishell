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
void	fill_new_entry(t_entry *entry, t_entry *new_entry, t_list **my_env);
void	fill_value_env(t_entry *new_entry, int context, char *value_env, int *j);
int		check_tild(t_entry *entry, int i);
void	keep_redirection(t_entry *entry, t_entry *new_entry, int *i, int *j);
void	copy_entry_value(t_entry *entry, t_entry *new_entry, int *i, int *j);
void	inc_size_after_chev(t_entry *entry, int *i, int *size);

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
			if (inc_size_of_var_value(my_env, entry, &i, &size) == -1)
				return (-1);
		else
		{
			size++;
			i++;
		}
	}
	return (size);
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

	// if (entry[i + 1].c && entry[i + 1].c == '?')
	// {
	// 	size += ft_strlen("42");
	// 	i += 2;
	// }
	// else
	// {
		name_env = get_name_env(entry, i);
		if (!name_env)
		{
			ft_error(ERROR_42, NULL);
			return (-1);
		}
		value_env = ft_getenv(my_env, name_env, 1);
		*size += ft_strlen(value_env);
		free(value_env);
	// }
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

void	fill_new_entry(t_entry *entry, t_entry *new_entry, t_list **my_env)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (entry[i].c)
	{
		//ft_printf("char %d : %c context : %d\n", i, entry[i].c, entry[i].context);
		if (entry[i].c == '$' && entry[i].context != SI_QUOTE && good_char_env(entry, i))
		{
			// if (entry[i + 1].c && entry[i + 1].c == '?')
			// {
			// 	fill_value_env(new_entry, entry[i].context, ft_strdup("42"), &j);
			// 	i += 2;
			// }
			// else
				fill_value_env(new_entry, entry[i].context, ft_getenv(my_env, get_name_env(entry, &i), 1), &j);
		}
		else if (entry[i].c == '~' && entry[i].context != SI_QUOTE && check_tild(entry, i))
		{
			fill_value_env(new_entry, entry[i].context, ft_getenv(my_env, "HOME", 0), &j);
			i++;
		}
		else if ((entry[i].type == CHEV_IN || entry[i].type == CHEV_OUT) && entry[i].context == 0)
			keep_redirection(entry, new_entry, &i, &j);
		else
		{
			if (entry[i].context == 0 && (entry[i].type == S_QUOTE || entry[i].type == D_QUOTE))
				i++;
			else
				copy_entry_value(entry, new_entry, &i, &j);
		}
	}
	new_entry[j].c = 0;
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
	if (entry[i + 1].c && (ft_isalnum(entry[i + 1].c) || entry[i + 1].c == '_' || entry[i + 1].c == '?'))
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
