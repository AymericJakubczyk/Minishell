/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:07:28 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/26 02:56:53 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_list **my_env, char *get_me, int do_free)
{
	t_list	*runner;
	int		size;

	size = 0;
	runner = *my_env;
	size = ft_strlen(get_me);
	while (runner != NULL && runner->content)
	{
		if (ft_strncmp(runner->content, get_me, size) == 0 && \
			(size == ft_equal_size(runner->content)))
		{
			if (do_free)
				free(get_me);
			return (skip_equal(runner->content));
		}
		runner = runner->next;
	}
	if (do_free)
		free(get_me);
	return (NULL);
}

void	ft_dup_env(char **env, t_list **my_env)
{
	int		runner;
	t_list	*new;

	if (!env)
	{
		ft_create_env(my_env);
		return ;
	}
	runner = 0;
	while (env[runner])
	{
		new = ft_lstnew(ft_strdup(env[runner]), -1);
		if (!new)
		{
			ft_lstclear(my_env, free);
			ft_error(ERROR_42, NULL, 12);
			exit (42);
		}
		ft_lstadd_back(my_env, new);
		runner++;
	}
}

void	ft_create_env(t_list **my_env)
{
	char	*pwd;
	char	*shlvl;
	t_list	*new;

	pwd = ft_strjoin("PWD=", ft_pwd(0));
	if (!pwd)
		return ;
	shlvl = ft_strdup("SHLVL = 0");
	if (!shlvl)
	{
		free(pwd);
		return ;
	}
	new = ft_lstnew(pwd, -1);
	if (!new)
		return (free(pwd), free(shlvl));
	ft_lstadd_back(my_env, new);
	new = ft_lstnew(shlvl, -1);
	if (!new)
		return (ft_lstclear(my_env, free), free(shlvl));
	ft_lstadd_back(my_env, new);
}
