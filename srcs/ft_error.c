/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:43:46 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/09 13:20:16 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/error.h"
#include "../inc/minishell.h"

void	ft_error(const char *error, char *problem)
{
	if (problem != NULL)
		ft_printf("bash : %s %s", problem, error);
	else
		ft_printf("bash : %s", error);
}
