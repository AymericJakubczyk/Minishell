/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:22:21 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/18 15:36:26 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_path(void);

char	*ft_get_prompt(t_list	**my_env)
{
	char	*prompt;
	char	*user;
	char	*path;

	user = ft_getenv(my_env, "USER", 0);
	if (user == NULL)
		user = ft_strdup("you");
	path = ft_get_path();
	prompt = ft_strjoin2(user, ft_strdup(":"));
	prompt = ft_strjoin2(prompt, path);
	prompt = ft_strjoin2(prompt, ft_strdup("$ "));
	if (!prompt)
	{
		ft_lstclear(my_env, free);
		rl_clear_history();
		ft_error(ERROR_42, NULL, 12);
		exit(12);
	}
	return (prompt);
}

static char	*ft_get_path(void)
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
