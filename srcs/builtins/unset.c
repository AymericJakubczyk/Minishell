/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:51:36 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/29 13:43:33 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alnum(char *str);

void	ft_unset(t_list **my_env, char *str)
{
	t_list	*runner;
	t_list	*tmp;
	int		size;

	g_errno = 0;
	if (is_alnum(str) == 0)
		return (ft_error(ERROR_22, str));
	size = ft_strlen(str);
	runner = *my_env;
	tmp = *my_env;
	while (runner != NULL)
	{
		if (ft_strncmp(runner->content, str, size) == 0)
		{
			free(runner->content);
			free(runner);
			tmp->next = runner->next;
		}
		tmp = runner;
		runner = runner->next;
	}
}

int	is_alnum(char *str)
{
	int	runner;

	runner = 0;
	while (str[runner])
	{
		if (ft_isalnum(str[runner]) == 0 && str[runner] != '_')
			return (0);
		runner++;
	}
	return (1);
}
