/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:37:54 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/12 18:35:55 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *verif_if_expand(char *str);
int get_context(char *str, int j);
char *do_expand(char *str, int i);
char *get_name(char *str, int j);
char *get_str_before_env(char *str, int j);
char *get_str_after_env(char *str, int j);

void expand(t_list *list)
{
	int i;

	i = 0;
	while (list)
	{
		list->content = verif_if_expand(list->content);
		list = list->next;
	}
}

char *verif_if_expand(char *str)
{
	int i;

	i = 0;
	//ft_printf("test : %s\n", str);
	while (str[i])
	{
		if (str[i] == '$' && get_context(str, i) != 1) //1 == simple quote
		{
			return (do_expand(str, i));
			// if (get_context(str, i) == 0) //0 == no quote
			// 	split_expand(str, t_parse *parse, int i);
		}
		i++;
	}
	return (str);
}

int get_context(char *str, int j)
{
	int i;
	char quote;

	i = 0;
	quote = 0;
	while (str[i] && i < j)
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote != 0 && str[i] == quote)
			quote = 0;
		i++;
	}
	ft_printf("context : %c\n", quote);
	if (quote == 0)
		return (0);
	if (quote == '\'')
		return (1);
	if (quote == '\"')
		return (2);
}

char *do_expand(char *str, int i)
{
	char *name_env;
	char *str_expand;
	
	str_expand = ft_strdup("");
	name_env = get_name(str, i);
	ft_printf("env : %s\n", name_env);
	str_expand = ft_strjoin2(str_expand, get_str_before_env(str, i));
	if (getenv(name_env))
		str_expand = ft_strjoin2(str_expand, ft_strdup(getenv(name_env)));
	str_expand = ft_strjoin2(str_expand, get_str_after_env(str, i + 1 + ft_strlen(name_env)));
	ft_printf("str expand: %s\n", str_expand);
	//free(str);
	return (str_expand);
}

char *get_name(char *str, int j)
{
	char *name;
	
	name = ft_strdup("");
	j++;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
	{
		name = ft_strjoin2(name, char_to_str(str[j]));
		j++;
	}
	return (name);
}

char *get_str_before_env(char *str, int j)
{
	char *str_before;
	int i;

	str_before = ft_strdup("");
	i = 0;
	while (str[i] && i < j)
	{
		str_before = ft_strjoin2(str_before, char_to_str(str[i]));
		i++;
	}
	return (str_before);
}

char *get_str_after_env(char *str, int j)
{
	char *str_after;

	str_after = ft_strdup("");
	while (str[j])
	{
		str_after = ft_strjoin2(str_after, char_to_str(str[j]));
		j++;
	}
	return (str_after);
}
