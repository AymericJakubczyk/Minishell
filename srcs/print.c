/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:59:13 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/11 15:33:20 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_entry(t_entry *entry)
{
	int	i;

	i = 0;
	ft_printf("print entry : \n");
	while (entry[i].c != 0)
	{
		ft_printf("%c | type : %i | context : %i\n", entry[i].c, entry[i].type, entry[i].context);
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
		ft_printf("%s \n", parse[i].str);
		i++;
	}
}
