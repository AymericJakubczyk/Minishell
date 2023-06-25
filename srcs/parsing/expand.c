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

void	expand(t_entry *entry, t_entry **new_entry, t_list **my_env)
{
	*new_entry = malloc(sizeof(t_entry) * (get_new_size(entry, my_env) + 1));
	//ft_printf("new_size : %d\n", get_new_size(entry));
	fill_new_entry(entry, *new_entry, my_env);
}

//refaire car maintenant j'interprete pas les variables dans les infile/outfile/limiter
int	get_new_size(t_entry *entry, t_list **my_env)
{
	int	i;
	int	size;
	int type;
	
	i = 0;
	size = 0;
	while (entry[i].c)
	{
		if ((entry[i].type == CHEV_IN || entry[i].type == CHEV_OUT) && entry[i].context == 0)
		{
			type = entry[i].type;
			while (type == entry[i].type)
			{
				i++;
				size++;
			}
			while (entry[i].c && entry[i].type == WHITESPACE)
			{
				i++;
				size++;
			}
			size += go_to_end_block(&entry[i]);
			i += go_to_end_block(&entry[i]);
			
		}
		else if (entry[i].c == '~' && entry[i].context != SI_QUOTE && check_tild(entry, i))
		{
			size += ft_strlen(ft_getenv(my_env, "HOME"));
			i++;
		}
		else if (entry[i].c == '$' && entry[i].context != SI_QUOTE && good_char_env(entry, i))
		{
			size += ft_strlen(ft_getenv(my_env, get_name_env(entry, &i)));
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

void	fill_new_entry(t_entry *entry, t_entry *new_entry, t_list **my_env)
{
	int	i;
	int	j;
	int size;
	char chev;

	j = 0;
	i = 0;
	while (entry[i].c)
	{
		//ft_printf("char %d : %c context : %d\n", i, entry[i].c, entry[i].context);
		if (entry[i].c == '$' && entry[i].context != SI_QUOTE && good_char_env(entry, i))
			fill_value_env(new_entry, entry[i].context, ft_getenv(my_env, get_name_env(entry, &i)), &j);
		else if (entry[i].c == '~' && entry[i].context != SI_QUOTE && check_tild(entry, i))
		{
			fill_value_env(new_entry, entry[i].context, ft_getenv(my_env, "HOME"), &j);
			i++;
		}
		else if ((entry[i].type == CHEV_IN || entry[i].type == CHEV_OUT) && entry[i].context == 0)
		{
			chev = entry[i].c;
			ft_printf("after chev\n");
			new_entry[j].c = entry[i].c;
			new_entry[j].type = entry[i].type;
			new_entry[j].context = entry[i].context;
			i++;
			j++;
			while (entry[i].c == chev)
			{
				new_entry[j].c = entry[i].c;
				new_entry[j].type = entry[i].type;
				new_entry[j].context = entry[i].context;
				i++;
				j++;
			}
			while (entry[i].c && entry[i].type == WHITESPACE)
				i++;
			size = go_to_end_block(&entry[i]);
			while (entry[i].c && size > 0)
			{
				//ft_printf("char : %c\n", entry[i].c);
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

int good_char_env(t_entry *entry, int i)
{
	if (entry[i + 1].c && (ft_isalnum(entry[i + 1].c) || entry[i + 1].c == '_'))
		return (1);
	return (0);
}

int check_tild(t_entry *entry, int i)
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
}
