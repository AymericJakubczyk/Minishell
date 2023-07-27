/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:34:47 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 04:03:21 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nbr_arg(t_parse *parse);
static int	fill_arg(t_parse *parse, char **arg);
static int	fill_cmd_arg(t_parse *parse, char **arg);

int	do_builtin(t_parse *parse, t_list **my_env, char **arg, t_exec *data)
{
	int		runner;
	char	*pwd;

	runner = 0;
	while (parse[runner].str && parse[runner].type != PIPEE)
	{
		if (parse[runner].type == COMMAND)
		{
			if (ft_strcmp(parse[runner].str, "echo") == 0)
				return (ft_echo(parse), 1);
			if (ft_strcmp(parse[runner].str, "env") == 0)
				return (ft_env(my_env, parse), 1);
			if (ft_strcmp(parse[runner].str, "pwd") == 0)
			{
				if (find_arg(parse) == -1)
					exit(g_errno);
				pwd = ft_pwd(1);
				return (ft_printf("%s\n", pwd), free(pwd), 1);
			}
			if (ft_strcmp(parse[runner].str, "export") == 0)
				return (ft_export(my_env, parse), 1);
			if (ft_strcmp(parse[runner].str, "exit") == 0)
				return (ft_exit(parse, my_env, arg, data), 1);
			if (ft_strcmp(parse[runner].str, "unset") == 0)
				return (ft_unset(my_env, parse), 1);
			if (ft_strcmp(parse[runner].str, "cd") == 0)
				return (ft_cd(my_env, parse), 1);
		}
		runner++;
	}
	return (0);
}

int	last_redir(t_parse *parse, int mode)
{
	int	type_redirect;
	int	i;

	type_redirect = -1;
	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (mode == IN && (parse[i].type == REDIRECT_IN \
			|| parse[i].type == HEREDOC))
			type_redirect = parse[i].type;
		if (mode == OUT && (parse[i].type == REDIRECT_OUT \
		|| parse[i].type == APPEND))
			type_redirect = parse[i].type;
		i++;
	}
	return (type_redirect);
}

char	*get_last_file(t_parse *parse, t_list **my_env, int mode)
{
	int	i;

	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
		i++;
	while (i >= 0)
	{
		if (mode == IN && parse[i].type == INFILE)
			return (expand_redirect(parse[i], my_env));
		if (mode == OUT && parse[i].type == OUTFILE)
			return (expand_redirect(parse[i], my_env));
		i--;
	}
	return (NULL);
}

char	**get_arg(t_parse *parse)
{
	char	**arg;
	int		size;

	size = get_nbr_arg(parse);
	if (size == 0)
		return (NULL);
	arg = malloc(sizeof(char *) * (size + 1));
	if (!arg)
		return (ft_error(ERROR_42, NULL, 1), NULL);
	if (fill_arg(parse, arg) == -1)
		return (ft_error(ERROR_42, NULL, 1), NULL);
	return (arg);
}

static int	get_nbr_arg(t_parse *parse)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == COMMAND || parse[i].type == CMD_ARG)
			nbr++;
		i++;
	}
	return (nbr);
}

static int	fill_arg(t_parse *parse, char **arg)
{
	int	i;
	int	num_arg;

	i = 0;
	num_arg = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == COMMAND)
		{
			arg[0] = ft_strdup(parse[i].str);
			if (!arg[0])
			{
				free(arg);
				return (-1);
			}
			num_arg++;
		}
		i++;
	}
	if (fill_cmd_arg(parse, arg) == -1)
		return (-1);
	return (0);
}

static int	fill_cmd_arg(t_parse *parse, char **arg)
{
	int	i;
	int	num_arg;

	num_arg = 1;
	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == CMD_ARG)
		{
			arg[num_arg] = ft_strdup(parse[i].str);
			if (!arg[num_arg])
			{
				free_all_tab(arg, num_arg);	
				return (-1);
			}
			num_arg++;
		}
		i++;
	}
	arg[num_arg] = NULL;
	return (0);
}
