/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:07:31 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/19 10:34:04 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_whitespaces(char	*array);

// int	ft_exit(char *array)
// {
// 	int		runner;
// 	int		count;
// 	char	*string;

// 	count = 0;
// 	runner = -1;
// 	if (ft_strcmp(array, "exit") == 0)
// 		return (-1);
// 	string = malloc(sizeof(char) * (no_whitespaces(array)) + 1);
// 	if (!string)
// 		return (-12);
// 	while (array[++runner])
// 	{
// 		if (array[runner] != ' ' && array[runner] != '\t')
// 		{
// 			string[count] = array[runner];
// 			count++;
// 		}
// 	}
// 	string[count] = '\0';
// 	if (ft_strcmp(string, "exit") == 0)
// 		return (free(string), -1);
// 	if ((ft_strncmp(string, "exit", 4) == 0) && (ft_strcmp(string, "exit") != 0))
// 		return (free(string), ft_error(ERROR_21, "exit", 2), -1);
// 	return (free(string), 0);
// }

// int	no_whitespaces(char	*array)
// {
// 	int	runner;
// 	int	count;

// 	count = 0;
// 	runner = 0;
// 	while (array[runner])
// 	{
// 		if (array[runner] != ' ' && array[runner] != '\t')
// 			count++;
// 		runner++;
// 	}
// 	return (count);
// }

void	ft_exit(t_parse *parse)
{
	int	arg;
	int	runner;

	runner = 0;
	while (parse[runner].str)
	{
		if (parse[runner].type == CMD_ARG)
		{
			arg = ft_atoi(parse[runner].str);
			if (arg != 0)
				exit(arg);
			else
			{
				ft_error("exit", parse[runner].str, 2);
				exit(2);
			}
		}
		runner++;
	}
	exit(1);
}
