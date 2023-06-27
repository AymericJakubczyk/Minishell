/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:07:28 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/26 16:15:30 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstfree(t_list **my_env);
void	ft_create_env(t_list **my_env);

char	*ft_getenv(t_list **my_env, char *get_me)
{
	t_list	*runner;
	int		size;

	size = 0;
	runner = *my_env;
	while (runner != NULL && runner->content)
	{
		if (runner->content)
		{
			size = ft_equal_size(runner->content);
			if (ft_strncmp(runner->content, get_me, size) == 0)
				return (skip_equal(runner->content));
			runner = runner->next;
		}
		else
			return (NULL);
	}
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
			ft_lstfree(my_env);
			ft_error(ERROR_42, NULL);
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

	pwd = ft_strjoin("PWD=", ft_pwd());
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
		return (ft_lstfree(my_env), free(shlvl));
	ft_lstadd_back(my_env, new);
}

void	ft_lstfree(t_list **my_env)
{
	t_list	*runner;
	t_list	*tmp;

	runner = *my_env;
	while (runner->next != NULL)
	{
		tmp = runner;
		free(runner->content);
		runner = runner->next;
		free(tmp);
	}
	free(runner->content);
	free(runner);
}
