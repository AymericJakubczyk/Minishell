/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:07:31 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/18 15:31:58 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_whitespaces(char	*array);

int	ft_exit(char *array)
{
	int		runner;
	int		count;
	char	*string;

	count = 0;
	runner = -1;
	if (ft_strcmp(array, "exit") == 0)
		return (-1);
	string = malloc(sizeof(char) * (no_whitespaces(array)) + 1);
	if (!string)
		return (-12);
	while (array[++runner])
	{
		if (array[runner] != ' ' && array[runner] != '\t')
		{
			string[count] = array[runner];
			count++;
		}
	}
	string[count] = '\0';
	if (ft_strcmp(string, "exit") == 0)
		return (free(string), -1);
	if ((ft_strncmp(string, "exit", 4) == 0) && (ft_strcmp(string, "exit") != 0))
		return (free(string), ft_error(ERROR_21, "exit", 2), -1);
	return (free(string), 0);
}

int	no_whitespaces(char	*array)
{
	int	runner;
	int	count;

	count = 0;
	runner = 0;
	while (array[runner])
	{
		if (array[runner] != ' ' && array[runner] != '\t')
			count++;
		runner++;
	}
	return (count);
}
