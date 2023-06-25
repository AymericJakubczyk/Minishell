/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:07:28 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/25 14:07:03 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	runner;

	runner = 0;
	while (env[runner])
	{
		ft_lstadd_back(my_env, ft_lstnew(ft_strdup(env[runner]), -1));
		runner++;
	}
}
