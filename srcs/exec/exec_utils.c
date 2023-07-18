/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:08:26 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/18 11:03:10 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	slash_in(char *str);
static char	**get_all_path(t_list **envp);
static int	check_env_path(char *str, char *str_path);
void		init_file(t_exec *data);

char	*get_path(char *cmd, t_list **env)
{
	char	**allpath;
	char	*test_path;
	char	*tmp;
	int		i;

	i = 0;
	if (cmd && slash_in(cmd))
	{
		if (access(cmd, F_OK | X_OK) != 0)
			return (ft_printf("no such file or directory: \n"), NULL);
		else
			return (cmd);
	}
	allpath = get_all_path(env);
	while (allpath && allpath[i])
	{
		tmp = ft_strjoin(allpath[i], "/");
		test_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(test_path, F_OK | X_OK) != -1)
			return (test_path);
		free(test_path);
		i++;
	}
	return (ft_printf("command not found: %s\n", cmd), NULL);
}

static int	slash_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	**get_all_path(t_list **envp)
{
	t_list	*runner;
	char	*path;
	char	**all_path;

	path = NULL;
	runner = *envp;
	while (runner->next && !path)
	{
		if (check_env_path(runner->content, "PATH=") == 1)
			path = runner->content;
		runner = runner->next;
	}
	if (!runner->content)
		return (NULL);
	all_path = ft_split(&path[5], ':');
	if (!all_path)
		return (NULL);
	return (all_path);
}

static int	check_env_path(char *str, char *str_path)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (str[i] != str_path[i])
			return (-1);
		i++;
	}
	return (1);
}

void	init_file(t_exec *data)
{
	data->current_fd_in = data->fd_in;
	data->current_fd_out = data->fd_out;
}
