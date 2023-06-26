/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:00:23 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/21 14:54:11 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == quote)
			quote = 0;
		else if (str[i] == '\'' && quote == 0)
			quote = '\'';
		else if (str[i] == '\"' && quote == 0)
			quote = '\"';
		i++;
	}
	if (quote != 0)
	{
		g_errno = 2;
		ft_printf("minihell: syntax error, quote %c is not close!\n", quote);
		return (0);
	}
	return (1);
}
