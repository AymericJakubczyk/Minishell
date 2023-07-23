/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:43:46 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/24 00:00:17 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"

void	ft_error(const char *error, char *problem, int nbrerror)
{
	if (nbrerror)
		g_errno = nbrerror;
	if (problem != NULL)
		ft_dprintf("(s)Hell : %s %s\n", problem, error);
	else
		ft_dprintf("(s)Hell : %s\n", error);
}
