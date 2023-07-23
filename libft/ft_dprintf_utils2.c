/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:06:00 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/23 01:05:10 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dputchar(char c, ssize_t *count)
{
	if (*count == -1)
		return ;
	if (write(2, &c, 1) == -1)
		*count = -1;
	else
		*count = *count + 1;
}

void	ft_dputstr(char *str, ssize_t *count)
{
	size_t	i;

	i = 0;
	if (!str)
	{
		ft_dputstr("(null)", count);
		return ;
	}
	while (str[i])
	{
		ft_dputchar(str[i], count);
		i++;
	}
}
