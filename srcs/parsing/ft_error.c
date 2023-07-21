/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:43:46 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/21 01:56:18 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"

void	ft_error(const char *error, char *problem, int nbrerror)
{
	if (nbrerror)
		g_errno = nbrerror;
	if (problem != NULL)
		ft_printf("(s)Hell : %s %s", problem, error);
	else
		ft_printf("(s)Hell : %s", error);
}
