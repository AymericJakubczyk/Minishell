/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:06:16 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/29 17:52:15 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parsing.h"

typedef struct s_exec
{
	int		nbr_limiter;
	char	**all_limiter;
	char	**str_heredoc;
	char	**env;
	int		fd_in;
	int		fd_out;
	int		mode;
}	t_exec;

// //do_heredoc.c
// void	do_heredoc(t_parse *parse, t_exec *my_struct, t_list **my_env);

// //expand_heredoc.c
// char	*expand_heredoc(char *str, t_list **my_env);
// //heredoc_utils.c
// int		quote_in(char *str);
// char	*limiter_without_quote(char *str);
// char	*ft_get_str_hd(t_parse *parse, t_exec *my_struct, int num_cmd);
// int		heredoc_in(t_parse *parse);

#endif