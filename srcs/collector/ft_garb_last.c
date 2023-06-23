/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garb_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:13:57 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/23 13:30:00 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_garb	*ft_garb_last(t_garb *garb)
{
	if (garb == 0)
		return (garb);
	while (garb -> next != 0)
	{
		garb = garb -> next;
	}
	return (garb);
}
