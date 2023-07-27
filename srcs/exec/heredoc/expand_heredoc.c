/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:01:28 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 01:03:14 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_in(char *str);
static char	*get_str_before_var(char *str, int *i);
static char	*get_name_env_hd(char *str, int *i);
static char	*get_str_after_var(char *str, int *i);

char	*expand_heredoc(char *str, t_list **my_env)
{
	char	*str_expanded;
	char	*getenv;
	int		i;

	if (!var_in(str))
		return (str);
	i = 0;
	str_expanded = ft_strdup("");
	str_expanded = ft_strjoin2(str_expanded, get_str_before_var(str, &i));
	if (str[i + 1] && str[i + 1] == '?')
	{
		str_expanded = ft_strjoin2(str_expanded, ft_itoa(g_errno));
		i += 2;
	}
	else
	{
		getenv = ft_getenv(my_env, get_name_env_hd(str, &i), 1);
		if (getenv != NULL)
			str_expanded = ft_strjoin2(str_expanded, getenv);
	}
	str_expanded = ft_strjoin2(str_expanded, get_str_after_var(str, &i));
	return (free(str), str_expanded);
}

static int	var_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || \
			str[i + 1] == '_' || str[i + 1] == '?'))
			return (1);
		i++;
	}
	return (0);
}

static char	*get_str_before_var(char *str, int *i)
{
	char	*str_before;

	str_before = ft_strdup("");
	while (str[*i] != '$')
	{
		str_before = ft_strjoin2(str_before, char_to_str(str[*i]));
		*i += 1;
	}
	return (str_before);
}

static char	*get_name_env_hd(char *str, int *i)
{
	char	*name_env;

	name_env = ft_strdup("");
	*i += 1;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		name_env = ft_strjoin2(name_env, char_to_str(str[*i]));
		*i += 1;
	}
	return (name_env);
}

static char	*get_str_after_var(char *str, int *i)
{
	char	*str_after;

	str_after = ft_strdup("");
	while (str[*i])
	{
		str_after = ft_strjoin2(str_after, char_to_str(str[*i]));
		*i += 1;
	}
	return (str_after);
}
