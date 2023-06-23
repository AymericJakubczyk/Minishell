/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garb_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:42:04 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/22 13:46:31 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_garb_clear(t_garb **garb)
{
	t_garb	*previous;
	t_garb	*trash;

	if (garb == 0 || *garb == 0)
		return ;
	previous = *garb;
	trash = *garb;
	while (trash)
	{
		previous = trash;
		trash = trash -> next;
		free(previous->malloc);
		free(previous);
	}
	garb = NULL;
}
