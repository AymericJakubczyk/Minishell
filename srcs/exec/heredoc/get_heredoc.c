/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 00:38:47 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 00:38:48 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_signal_hd(t_exec *data, t_heredoc *struct_hd);
static void	have_limiter(t_exec *data, t_heredoc *struct_hd);
static void	add_line_hd(t_exec *data, t_heredoc *struct_hd, t_list **my_env);

void	get_heredoc(t_exec *data, t_list **my_env)
{
	t_heredoc	struct_hd;

	struct_hd.stdin_copy = dup(0);
	struct_hd.i = 0;
	struct_hd.limiter = lim_without_quote(data->all_limiter[struct_hd.i]);
	struct_hd.quote_in_lim = quote_in(data->all_limiter[struct_hd.i]);
	g_errno = 0;
	while (struct_hd.i < data->nbr_limiter)
	{
		struct_hd.str = readline(">");
		if (!struct_hd.str)
		{
			if (check_signal_hd(data, &struct_hd))
				break ;
		}
		else if (ft_strcmp(struct_hd.str, struct_hd.limiter) == 0)
			have_limiter(data, &struct_hd);
		else
			add_line_hd(data, &struct_hd, my_env);
	}
	data->str_heredoc[struct_hd.i] = NULL;
}

static int	check_signal_hd(t_exec *data, t_heredoc *struct_hd)
{
	struct_hd->i += 1;
	if (g_errno == 130)
	{
		ft_printf("\n");
		data->str_heredoc[data->nbr_limiter] = NULL;
		dup2(struct_hd->stdin_copy, 0);
		close(struct_hd->stdin_copy);
		free(struct_hd->limiter);
		//free tout
		return (1);
	}
	else
		ft_dprintf("minihell: warning: here-document delimited by end-of-file \
					(wanted '%s')\n", struct_hd->limiter);
	free(struct_hd->limiter);
	if (struct_hd->i < data->nbr_limiter)
	{
		struct_hd->limiter = lim_without_quote(data->all_limiter[struct_hd->i]);
		struct_hd->quote_in_lim = quote_in(data->all_limiter[struct_hd->i]);
	}
	return (0);
}

static void	have_limiter(t_exec *data, t_heredoc *struct_hd)
{
	free(struct_hd->str);
	free(struct_hd->limiter);
	struct_hd->i += 1;
	if (struct_hd->i < data->nbr_limiter)
	{
		struct_hd->limiter = lim_without_quote(data->all_limiter[struct_hd->i]);
		struct_hd->quote_in_lim = quote_in(data->all_limiter[struct_hd->i]);
	}
}

static void	add_line_hd(t_exec *data, t_heredoc *struct_hd, t_list **my_env)
{
	if (!struct_hd->quote_in_lim)
		struct_hd->str = expand_heredoc(struct_hd->str, my_env);
	struct_hd->str = ft_strjoin2(struct_hd->str, ft_strdup("\n"));
	data->str_heredoc[struct_hd->i] = \
		ft_strjoin2(data->str_heredoc[struct_hd->i], struct_hd->str);
}
