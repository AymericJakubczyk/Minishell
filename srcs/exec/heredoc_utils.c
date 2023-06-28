/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:04:24 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/28 18:04:25 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_in(t_parse *parse)
{
	int	i;

	i = 0;
	while (parse[i].str)
	{
		if (parse[i].type == HEREDOC)
			return (1);
		i++;
	}
	return (0);
}

int	quote_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*limiter_without_quote(char *str)
{
	char	quote;
	int		i;
	char	*limiter;

	quote = 0;
	i = 0;
	limiter = ft_strdup("");
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			limiter = ft_strjoin2(limiter, char_to_str(str[i]));
		i++;
	}
	return (limiter);
}

char	*ft_get_str_hd(t_parse *parse, t_exec *my_struct, int num_cmd)
{
	int	i;
	int	cmd;
	int	num_hd;

	i = 0;
	cmd = 1;
	num_hd = 0;
	while (cmd <= num_cmd && parse[i].str)
	{
		if (parse[i].type == PIPEE)
			cmd++;
		else if (parse[i].type == LIMITER)
			num_hd++;
		i++;
	}
	return (my_struct->str_heredoc[num_hd - 1]);
}
