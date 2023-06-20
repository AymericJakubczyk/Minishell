/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:48 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/20 16:31:27 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_echo(t_list *lst)
// {
// 	t_list	*liste;
// 	char	*string;
// 	int		type;

// 	type = 0;
// 	liste = lst;
// 	if (ft_strncmp(lst->content, '-n', 2) == 0)
// 		type = -1;
// 	string = ft_strdup(lst->content);
// 	if (lst->next)
// 		lst = lst->next;
// 	while (lst->next && (lst->content[0] != '|' || \
// 	lst->content[0] != '<' || lst->content[0] != '>'))
// 	{
// 		string = ft_strjoin3(string, ' ');
// 		string = ft_strjoin3(string, lst->content);
// 		lst = lst->next;
// 	}
// 	if (type > 0)
// 		string = ft_strjoin3(string, '\n');
// 	return (string);
// }

void	ft_env(char **env)
{
	int		runner;

	runner = 0;
	while (env[runner])
	{
		ft_printf("%s\n", env[runner]);
		runner++;
	}
}

char	*ft_pwd()
{
	char	*path;
	int		size;

	size = 40;
	path = malloc(sizeof(char) * (size + 1));
	getcwd(path, size);
	return (path);
}

void	ft_cd(char *directory)
{
	if (!directory)
		chdir("/nfs/homes");
	chdir(directory);
}
