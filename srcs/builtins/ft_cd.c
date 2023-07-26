/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:59:14 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/26 02:56:26 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_list **my_env, t_parse *parse)
{
	char	*oldpwd;
	int		count;
	int		flag;

	count = 0;
	flag = 0;
	cd_errors(&count, &flag, parse);
	if (count > 1)
		return (ft_error(ERROR_23, "cd", 1));
	if (check_dir(parse[flag].str) == -1 && flag != 0)
		return (ft_error(ERROR_99, NULL, 1));
	oldpwd = ft_strjoin4("OLDPWD=", ft_pwd(0));
	if (oldpwd == NULL)
		oldpwd = ft_getenv(my_env, "OLDPWD", 0);
	do_ft_export(my_env, oldpwd);
	next_cd(my_env, parse[flag].str, oldpwd);
}

void	cd_errors(int *count, int *flag, t_parse *parse)
{
	int	runner;

	runner = 0;
	while (parse[runner].str && parse[runner++].type != PIPEE)
	{
		if (parse[runner].type == CMD_ARG)
		{
			if (parse[runner].str[0] == '-')
			{
				if (parse[runner].str[1] == '-')
					return (ft_error(ERROR_25, "--", 2));
				return (ft_error(ERROR_25, parse[runner].str, 2));
			}
			*count += 1;
			*flag = runner;
		}
	}
}

void	next_cd(t_list **my_env, char *str, char *oldpwd)
{
	char	*pwd;
	char	*home;

	free(oldpwd);
	home = ft_getenv(my_env, "HOME", 0);
	if (!home)
		return ;
	if (!str || ft_strncmp(str, "cd", 2) == 0)
	{
		if (chdir(home) != 0)
			ft_error(ERROR_99, NULL, 1);
	}
	else if (chdir(str) != 0)
	{
		ft_error(ERROR_99, NULL, 1);
		return (free(home));
	}
	free(home);
	pwd = ft_strjoin4("PWD=", ft_pwd(0));
	do_ft_export(my_env, pwd);
	free(pwd);
	g_errno = 0;
}
