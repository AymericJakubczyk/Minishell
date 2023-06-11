/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:00:23 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/11 18:16:33 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax_quote(char *str)
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
		ft_printf("syntax error!\n");
		//exit(2);
	}
	// else
		// ft_printf("good quote\n");
}
