/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:22:21 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/27 12:30:11 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_path(t_list **my_env);
static int	is_in_path(char *home, char *path);
static char	*replace_in_path(char *home, char *path);

char	*ft_get_prompt(t_list	**my_env)
{
	char	*prompt;
	char	*user;
	char	*path;

	user = ft_getenv(my_env, "USER", 0);
	if (user == NULL)
		user = "you";
	path = ft_get_path(my_env);
	prompt = ft_strjoin2(user, ft_strdup(":"));
	prompt = ft_strjoin2(prompt, path);
	prompt = ft_strjoin2(prompt, ft_strdup("$ "));
	if (!prompt)
	{
		ft_lstclear(my_env, free);
		rl_clear_history();
		ft_error(ERROR_42, NULL);
		exit(12);
	}
	return (prompt);
}

static char	*ft_get_path(t_list **my_env)
{
	char	*path;
	char	*output;
	int		runner;
	int		tmp;

	tmp = 0;
	path = ft_pwd();
	runner = 0;
	while (path[runner])
	{
		if (path[runner] == '/')
			tmp = runner;
		runner++;
	}
	output = ft_strdup(&path[++tmp]);
	free(path);
	if (!output)
		return (NULL);
	return (output);
}

// static int	is_in_path(char *home, char *path)
// {
// 	int	i;

// 	i = 0;
// 	while (home[i] && path[i] && home[i] == path[i])
// 		i++;
// 	if (home[i] == '\0')
// 		return (1);
// 	else
// 		return (0);
// }

// static char	*replace_in_path(char *home, char *path)
// {
// 	int		i;
// 	char	*new_path;

// 	i = 0;
// 	while (home[i] && path[i] && home[i] == path[i])
// 		i++;
// 	new_path = ft_strjoin("~", &path[i]);
// 	free(path);
// 	return (new_path);
// }
