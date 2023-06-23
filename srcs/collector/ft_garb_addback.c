/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garb_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:39:02 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/23 13:27:34 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_garb_addback(t_garb **garb, t_garb *trash)
{
	t_garb	*last;

	if (garb == 0)
		return ;
	last = ft_garb_last(*garb);
	if (last == 0)
		*garb = trash;
	else
		last -> next = trash;
}
