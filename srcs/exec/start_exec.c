/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:05:40 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/23 18:38:03 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_parse *parse, t_list **my_env, int runner);

void	start_exec(t_parse *parse, t_list **my_env)
{
	int	runner;

	runner = 0;
	while (parse[runner].str)
	{
		if (parse[runner].type && parse[runner].type == COMMAND)
		{
			runner = is_builtin(parse, my_env, runner);
		}
		runner++;
	}
}

int	is_builtin(t_parse *parse, t_list **my_env, int runner)
{
	char	*arg;

	if (ft_strcmp(parse[runner].str, "echo") == 0)
	{
		arg = ft_strdup(parse[++runner].str);
		// ft_printf("%s\n", arg);
		while (parse[++runner].type == CMD_ARG)
		{
			arg = ft_strjoin3(arg, " ");
			arg = ft_strjoin3(arg, parse[runner].str);
		}
		ft_echo(arg);
		return (runner);
	}
	if (ft_strcmp(parse[runner].str, "export") == 0)
	{
		ft_export(my_env, parse[++runner].str);
		return (runner);
	}
	if (ft_strcmp(parse[runner].str, "unset") == 0)
		ft_unset(my_env, parse[++runner].str);
	if (ft_strcmp(parse[runner].str, "pwd") == 0)
		ft_printf("%s\n",ft_pwd());
	if (ft_strcmp(parse[runner].str, "env") == 0)
	{
		if (parse[runner + 1].str)
			return (runner);
		ft_env(my_env);
	}
	if (ft_strcmp(parse[runner].str, "cd") == 0)
	{
		if (parse[runner + 2].str && parse[runner + 2].type == CMD_ARG)
			ft_error(ERROR_23, parse[runner].str);
		ft_cd(parse[++runner].str, my_env);
	}
	return (runner);
}
