/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 06:31:08 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 14:31:01 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_all_path(t_list **envp);
// static int	check_env_path(char *str, char *str_path);
static char	*verif_path(char *cmd, char **allpath, int *i);

char	*get_path(char *cmd, t_list **env, t_exec *data)
{
	char	**allpath;
	char	*test_path;
	int		i;

	i = 0;
	if (cmd && slash_in(cmd))
	{
		if (is_directory(cmd, env, data))
			return (NULL);
		else
			return (cmd);
	}
	allpath = get_all_path(env);
	if (!allpath)
		return (NULL);
	while (allpath && allpath[i])
	{
		test_path = verif_path(cmd, allpath, &i);
		if (test_path)
			return (free_all(allpath), test_path);
	}
	ft_error(ERROR_12, cmd, 127);
	return (free_all(allpath), free_minishell(data, env), exit(g_errno), NULL);
}

// char	*get_path(char *cmd, t_list **env, t_parse *parse)
// {
// 	char	**allpath;
// 	char	*test_path;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	if (cmd && slash_in(cmd))
// 	{
// 		if (is_directory(cmd, parse, env))
// 			return (NULL);
// 		else
// 			return (cmd);
// 	}
// 	allpath = get_all_path(env);
// 	if (!allpath)
// 		return (NULL);
// 	while (allpath && allpath[i])
// 	{
// 		tmp = ft_strjoin(allpath[i], "/");
// 		test_path = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (access(test_path, F_OK | X_OK) != -1)
// 			return (free_all(allpath), test_path);
// 		free(test_path);
// 		i++;
// 	}
// 	ft_error(ERROR_12, cmd, 127);
// 	free_all(allpath);
// 	free_all_parse(parse);
// 	rl_clear_history();
// 	return (ft_lstclear(env, free), exit(g_errno), NULL);
// }

static char	**get_all_path(t_list **envp)
{
	t_list	*runner;
	char	*path;
	char	**all_path;

	path = NULL;
	runner = *envp;
	path = ft_getenv(envp, "PATH", 0);
	if (path == NULL)
		return (NULL);
	all_path = ft_split(path, ':');
	free(path);
	if (!all_path)
		return (NULL);
	return (all_path);
}

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

static char	*verif_path(char *cmd, char **allpath, int *i)
{
	char	*test_path;
	char	*tmp;

	tmp = ft_strjoin(allpath[*i], "/");
	test_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (access(test_path, F_OK | X_OK) != -1)
		return (test_path);
	free(test_path);
	*i += 1;
	return (NULL);
}
