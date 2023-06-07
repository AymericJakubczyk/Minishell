/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:14:32 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/07 13:23:53 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_chev(t_entry *entry, char type);

void	check_syntax(t_entry *entry)
{
	check_chev(entry, '<');
	check_chev(entry, '>');
	check_pipe(entry);
	check_quote(entry, '\'');
	check_quote(entry, '\"');
}

void	check_chev(t_entry *entry, char type)
{
	int	index;
	int	count;

	count = 0;
	index = 0;
	while (entry[index].c)
	{
		if (entry[index].c == type)
			count++;
		else
			count = 0;
		if (count == 3 && entry[index + 1].c && entry[index + 1].c == type)
			return (ft_printf("syntax error near unexpected token : %c%c\n", type, type), exit(1));
		else if (count == 3)
			return (ft_printf("syntax error near unexpected token : %c\n", type), exit(1));
		index++;
	}
}

void	check_pipe(t_entry *entry)
{
	int	index;
	int	count;

	count = 0;
	index = 0;
	if (entry[0].c == '|')
		return (ft_printf("syntax error near unexpected token : |\n"), exit(1));
	while (entry[index].c)
	{
		if (entry[index].c == '|')
			count++;
		else
			count = 0;
		if (count == 2)
			return (ft_printf("syntax error near unexpected token : ||\n"), exit(1));
		index++;
	}
}

void	check_quote(t_entry *entry, char type)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (entry[index].c)
	{
		if (entry[index].c == type)
			count++;
		index++;
	}
	if ((count % 2) != 0)
		return (ft_printf("Line can't end with open : %c\n", type), exit(1));
}
