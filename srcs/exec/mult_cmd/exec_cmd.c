/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 06:54:36 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 06:54:39 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	verif_and_do_redir(t_parse *parse, int num_cmd, t_list **my_env, \
								t_exec *data);
static int	do_builtin(t_parse *parse, t_list **my_env, char **arg, \
						t_exec *data);
static int	next_do_builtin(t_parse *parse, t_list **my_env, int runner);
static char	*get_str_cmd(t_parse *parse);

void	exec_cmd(t_parse *parse, int num_cmd, t_list **my_env, t_exec *data)
{
	char	**arg;
	char	*path;
	int		start_cmd;

	start_cmd = get_start_cmd(parse, num_cmd);
	verif_and_do_redir(parse, num_cmd, my_env, data);
	arg = get_arg(&parse[start_cmd]);
	if (!arg)
		return ;
	if (do_builtin(&parse[start_cmd], my_env, arg, data))
	{
		free_all(arg);
		free_minishell(data, my_env);
		exit(0);
	}
	path = get_path(arg[0], my_env, data);
	if (!path)
		return ;
	execve(path, arg, data->env);
	if (ft_strlen(get_str_cmd(&parse[start_cmd])) != 0)
		ft_error(strerror(errno), get_str_cmd(&parse[start_cmd]), errno);
	else
		ft_error(ERROR_12, "\'\'", 127);
	exit(g_errno);
}

static void	verif_and_do_redir(t_parse *parse, int num_cmd, t_list **my_env, \
								t_exec *data)
{
	int		start_cmd;

	start_cmd = get_start_cmd(parse, num_cmd);
	if (!check_all_redirect(&parse[start_cmd], my_env, data))
		exit (1);
	if (redirect_in_cmd(&parse[start_cmd], IN))
		do_redirect_in(&parse[start_cmd], my_env, data, num_cmd);
	else
		do_classique_pipe(num_cmd, data, IN);
	if (redirect_in_cmd(&parse[start_cmd], OUT))
		do_redirect_out(&parse[start_cmd], my_env, data);
	else
		do_classique_pipe(num_cmd, data, OUT);
}

static int	do_builtin(t_parse *parse, t_list **my_env, char **arg, \
						t_exec *data)
{
	int		runner;
	char	*pwd;

	runner = 0;
	while (parse[runner].str && parse[runner].type != PIPEE)
	{
		if (parse[runner].type == COMMAND)
		{
			if (ft_strcmp(parse[runner].str, "exit") == 0)
				return (ft_exit(parse, my_env, arg, data), 1);
			else if (ft_strcmp(parse[runner].str, "pwd") == 0)
			{
				if (find_arg(parse) == -1)
					exit(g_errno);
				pwd = ft_pwd(1);
				return (ft_printf("%s\n", pwd), free(pwd), 1);
			}
			else if (next_do_builtin(parse, my_env, runner))
				return (1);
		}
		runner++;
	}
	return (0);
}

static int	next_do_builtin(t_parse *parse, t_list **my_env, int runner)
{
	if (ft_strcmp(parse[runner].str, "echo") == 0)
		return (ft_echo(parse), 1);
	if (ft_strcmp(parse[runner].str, "env") == 0)
		return (ft_env(my_env, parse), 1);
	if (ft_strcmp(parse[runner].str, "export") == 0)
		return (ft_export(my_env, parse), 1);
	if (ft_strcmp(parse[runner].str, "unset") == 0)
		return (ft_unset(my_env, parse), 1);
	if (ft_strcmp(parse[runner].str, "cd") == 0)
		return (ft_cd(my_env, parse), 1);
	return (0);
}

static char	*get_str_cmd(t_parse *parse)
{
	int	i;

	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == COMMAND)
			return (parse[i].str);
		i++;
	}
	return (NULL);
}
