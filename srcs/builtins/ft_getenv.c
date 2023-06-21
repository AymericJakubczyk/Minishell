/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:07:28 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/21 15:07:40 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_dup_env(char **env, t_list **my_env)
{
	int	runner;

	runner = 0;
	while (env[runner])
	{
		ft_lstadd_back(my_env, ft_lstnew(ft_strdup(env[runner]), -1));
		runner++;
	}
}