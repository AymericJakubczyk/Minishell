/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:13:46 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/21 23:08:59 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_new_size(t_entry *entry);
char	*get_name_env(t_entry *entry, int *i);
void	fill_new_entry(t_entry *entry, t_entry *new_entry);
void	fill_value_env(t_entry *new_entry, int context, char *value_env, int *j);

void	expand(t_entry *entry, t_entry **new_entry)
{
	*new_entry = malloc(sizeof(t_entry) * (get_new_size(entry) + 1));
	//ft_printf("new_size : %d\n", get_new_size(entry));
	fill_new_entry(entry, *new_entry);
}


//refaire car maintenant j'interprete pas les variables dans les infile/outfile/limiter
int	get_new_size(t_entry *entry)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (entry[i].c)
	{
		if (entry[i].c == '$' && entry[i].context != SI_QUOTE)
		{
			size += ft_strlen(getenv(get_name_env(entry, &i)));
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
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

void	fill_new_entry(t_entry *entry, t_entry *new_entry)
{
	int	i;
	int	j;
	int size;

	j = 0;
	i = 0;
	while (entry[i].c)
	{
		//ft_printf("char %d : %c context : %d\n", i, entry[i].c, entry[i].context);
		if (entry[i].c == '$' && entry[i].context != SI_QUOTE)
			fill_value_env(new_entry, entry[i].context, getenv(get_name_env(entry, &i)), &j);
		else if ((entry[i].type == CHEV_IN || entry[i].type == CHEV_OUT) && entry[i].context == 0)
		{
			ft_printf("after chev\n");
			new_entry[j].c = entry[i].c;
			new_entry[j].type = entry[i].type;
			new_entry[j].context = entry[i].context;
			i++;
			j++;
			while (entry[i].c && entry[i].type == WHITESPACE)
				i++;
			size = go_to_end_block(&entry[i]);
			while (entry[i].c && size > 0)
			{
				new_entry[j].c = entry[i].c;
				new_entry[j].type = entry[i].type;
				new_entry[j].context = entry[i].context;
				size--;
				i++;
				j++;
			}
		}
		else
		{
			if (entry[i].context == 0 && (entry[i].type == S_QUOTE || entry[i].type == D_QUOTE))
				i++;
			else
			{
				new_entry[j].c = entry[i].c;
				new_entry[j].type = entry[i].type;
				new_entry[j].context = entry[i].context;
				i++;
				j++;
			}
		}
	}
	new_entry[j].c = 0;
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
}
