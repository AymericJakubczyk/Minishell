/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:08:26 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/23 16:44:35 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_path(char *cmd, char **env)
// {
// 	char	**allpath;
// 	char	*test_path;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	if (cmd && slash_in(cmd))
// 	{
// 		if (access(cmd, F_OK | X_OK) != 0)
// 			return (ft_perr("no such file or directory: ", cmd, "\n"), NULL);
// 		else
// 			return (cmd);
// 	}
// 	allpath = get_all_path(env);
// 	while (allpath && allpath[i])
// 	{
// 		tmp = ft_strjoin(allpath[i], "/");
// 		test_path = ft_strjoin(tmp, cmd);
// 		ft_free(tmp);
// 		if (access(test_path, F_OK | X_OK) != -1)
// 			return (free_all(allpath), test_path);
// 		ft_free(test_path);
// 		i++;
// 	}
// 	return (free_all(allpath), ft_perr("command not found: ", cmd, "\n"), NULL);
// }

// static int	slash_in(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '/')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// static char	**get_all_path(char **envp)
// {
// 	int		i;
// 	char	*path;
// 	char	**all_path;

// 	path = NULL;
// 	i = 0;
// 	while (envp[i] && !path)
// 	{
// 		if (check_env_path(envp[i], "PATH=") == 1)
// 			path = envp[i];
// 		i++;
// 	}
// 	if (!envp[i])
// 		return (NULL);
// 	all_path = ft_split(&path[5], ':');
// 	if (!all_path)
// 		return (NULL);
// 	return (all_path);
// }

// static int	check_env_path(char *str, char *str_path)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 5)
// 	{
// 		if (str[i] != str_path[i])
// 			return (-1);
// 		i++;
// 	}
// 	return (1);
// }
