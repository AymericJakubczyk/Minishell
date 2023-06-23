/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garb_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:46:46 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/22 13:49:09 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_garb	*ft_garb_new(void *addr)
{
	t_garb	*trash;

	trash = malloc(sizeof(t_garb));
	if (trash == 0)
		return (0);
	trash->malloc = addr;
	trash->next = 0;
	return (trash);
}
