/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:16:13 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/11/19 18:27:47 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	i = 0;
	if (count != 0 && SIZE_MAX / count < size)
		return (0);
	mem = malloc(count * size);
	if (mem == 0)
		return (0);
	while (i < count * size)
	{
		mem[i] = '\0';
		i++;
	}
	return (mem);
}
