/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:47:06 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/27 16:43:56 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fill_quoter(char *str, int size, char *output);

char	*add_quotes(char *str)
{
	int		size;
	char	*output;
	int		runner;

	output = NULL;
	if (ft_strlen(str) == (size_t)ft_equal_size(str))
		return (ft_strdup(str));
	runner = 0;
	size = ft_strlen(str);
	output = fill_quoter(str, size, output);
	if (output == NULL)
		return (ft_error(ERROR_42, NULL, 1), NULL);
	return (output);
}

static char	*fill_quoter(char *str, int size, char *output)
{
	int	runner;

	runner = 0;
	output = malloc(sizeof(char) * (size + 3));
	if (!output)
		return (NULL);
	while (str[runner] && str[runner] != '=')
	{
		output[runner] = str[runner];
		runner++;
	}
	output[runner++] = '=';
	output[runner] = '\"';
	runner++;
	while (str[runner - 1])
	{
		output[runner] = str[runner - 1];
		runner++;
	}
	output[runner] = '\"';
	output[++runner] = '\0';
	return (output);
}

int	equal(char *str)
{
	int	runner;

	runner = 0;
	while (str[runner])
	{
		if (str[runner] == '=')
			return (1);
		runner++;
	}
	return (0);
}

int	check_dir(char *str)
{
	int	fd;

	fd = open(str, O_DIRECTORY);
	if (fd == -1)
		return (-1);
	return (0);
}

void	do_ft_export(t_list **my_env, char *str)
{
	g_errno = 0;
	if (is_allready_export(my_env, str))
		export_again(my_env, str);
	else
		ft_lstadd_back(my_env, ft_lstnew(ft_str_skip_add(str), -1));
}
