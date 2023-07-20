/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:47:06 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/21 01:15:56 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_quotes(char *str)
{
	int		size;
	char	*output;
	int		runner;

	if (ft_strlen(str) == (size_t)ft_equal_size(str))
		return (str);
	runner = 0;
	size = ft_strlen(str);
	output = malloc(sizeof(char) * (size + 3));
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

void	next_cd(t_list **my_env, char *str)
{
	char	*pwd;
	char	*home;

	home = ft_getenv(my_env, "HOME", 0);
	if (!home)
		return ;
	if (!str)
	{
		if (chdir(home) != 0)
			ft_error(ERROR_99, NULL, 1);
	}
	else if (chdir(str) != 0)
	{
		ft_error(ERROR_99, NULL, 1);
		return ;
	}
	pwd = ft_strjoin4("PWD=", ft_pwd(0));
	do_ft_export(my_env, pwd);
}

void	do_ft_export(t_list **my_env, char *str)
{
	t_list	*tmp;

	g_errno = 0;
	tmp = *my_env;
	if (is_allready_export(my_env, str))
		export_again(my_env, str);
	else
		ft_lstadd_back(my_env, ft_lstnew(ft_str_skip_add(str), -1));
}
