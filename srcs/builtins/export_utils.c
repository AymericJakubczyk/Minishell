/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:06:32 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/21 21:05:35 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_allready_export(t_list **my_env, char *str)
{
	t_list	*runner;

	runner = *my_env;
	while (runner != NULL)
	{
		if (ft_strncmp(runner->content, str, ft_equal_size(str)) == 0)
			return (1);
		runner = runner->next;
	}
	return (0);
}

int	ft_equal_size(char *str)
{
	size_t	runner;

	runner = 0;
	if (!str)
		return (0);
	while (str[runner] && str[runner] != '=')
		runner++;
	return (runner);
}

char	*skip_equal(char *str)
{
	int	runner;

	runner = ft_equal_size(str);
	if (ft_strlen(str) - runner < 1)
		return (" ");
	return (ft_substr(str, runner + 1, (ft_strlen(str) - runner)));
}

char	*ft_str_skip_add(char *str)
{
	int		runner;
	int		index;
	int		count;
	char	*output;

	index = 0;
	runner = 0;
	count = ft_strlen(str);
	output = malloc(sizeof(char) * count + 1);
	if (!output)
		return (NULL);
	while (runner < count)
	{
		if (str[runner] == '+')
			runner++;
		output[index] = str[runner];
		runner++;
		index++;
	}
	output[index] = '\0';
	return (output);
}

int	is_addition(char *str)
{
	int	runner;

	runner = 0;
	while (str[runner] && str[runner] != '=')
		runner++;
	if (str[runner] - 1 && str[runner - 1] == '+')
		return (1);
	return (0);
}
