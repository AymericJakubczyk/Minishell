/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:18:09 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/14 13:19:57 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_equal(char *str);
int		ft_equal_size(char *str);

void	ft_export(t_list **my_env, char *str)
{
	ft_lstadd_back(my_env, ft_lstnew(ft_strdup(str), -1));
}

void	ft_dup_env(char **env, t_list **my_env)
{
	int		runner;

	runner = 0;
	//if (!env)
	// creer un env
	while (env[runner])
	{
		ft_lstadd_back(my_env, ft_lstnew(ft_strdup(env[runner]), -1));
		runner++;
	}
}

void	ft_add_var(t_list **my_env, char *str)
{
	ft_lstadd_back(my_env, ft_lstnew(ft_strdup(str), -1));
}

char	*ft_getenv(t_list **my_env, char *get_me)
{
	t_list	*runner;
	int		size;

	size = 0;
	runner = *my_env;
	while (runner != NULL)
	{
		size = ft_equal_size(runner->content);
		if (ft_strncmp(runner->content, get_me, size) == 0)
			return (skip_equal(runner->content));
		runner = runner->next;
	}
	return (NULL);
}

int	ft_equal_size(char *str)
{
	int	runner;

	runner = 0;
	while (str[runner] && str[runner] != '=')
	{
		runner++;
	}
	return (runner);
}

char	*skip_equal(char *str)
{
	int		runner;

	runner = ft_equal_size(str);
	if (ft_strlen(str) - runner < 1)
		return (" ");
	return (ft_substr(str, runner + 1, (ft_strlen(str) - runner)));
}
