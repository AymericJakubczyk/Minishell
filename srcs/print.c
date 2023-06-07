/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:59:13 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/07 12:48:32 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_entry(t_entry *entry)
{
	int	i;

	i = 0;
	ft_printf("print entry : \n");
	while (entry[i].c != 0)
	{
		ft_printf("%c : %i\n", entry[i].c, entry[i].type);
		i++;
	}
}

void	print_parse(t_parse *parse)
{
	int	i;

	i = 0;
	ft_printf("print parse : \n");
	while (parse[i].str)
	{
		ft_printf("%s : %i\n", parse[i].str, parse[i].type);
		i++;
	}
}
