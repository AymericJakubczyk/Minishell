/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:10:46 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/26 06:39:07 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirect(t_parse parse, t_list **my_env, int mode);

int	check_all_redirect(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	i;

	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == REDIRECT_IN && \
		!check_redirect(parse[i + 1], my_env, IN))
		{
			ft_lstclear(my_env, free);
			free_all_parse(data->parse);
			rl_clear_history();
			return (0);
		}
		else if ((parse[i].type == REDIRECT_OUT || parse[i].type == APPEND) \
		&& !check_redirect(parse[i + 1], my_env, OUT))
		{
			ft_lstclear(my_env, free);
			free_all_parse(data->parse);
			rl_clear_history();
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_all_redirect_without_fork(t_parse *parse, t_list **my_env)
{
	int	i;

	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == REDIRECT_IN && \
		!check_redirect(parse[i + 1], my_env, IN))
		{
			return (0);
		}
		else if ((parse[i].type == REDIRECT_OUT || parse[i].type == APPEND) \
		&& !check_redirect(parse[i + 1], my_env, OUT))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_redirect(t_parse parse, t_list **my_env, int mode)
{
	char	*expanded;

	expanded = expand_redirect(parse, my_env);
	if (!expanded)
		return (0);
	if (mode == IN && access(expanded, F_OK | R_OK) == -1)
	{
		ft_dprintf("(s)Hell : %s: %s\n", expanded, strerror(errno));
		return (free(expanded), 0);
	}
	if (mode == OUT && open(expanded, O_WRONLY | O_CREAT, 0644) == -1)
	{
		ft_dprintf("(s)Hell : %s: %s\n", expanded, strerror(errno));
		return (free(expanded), 0);
	}
	return (free(expanded), 1);
}
