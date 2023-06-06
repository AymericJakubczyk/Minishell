/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:32:42 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/11/19 18:32:45 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	int		j;
	int		to_return;

	if (dst == 0 && dstsize == 0)
		return (ft_strlen(src));
	to_return = ft_strlen(src) + ft_strlen(dst);
	i = ft_strlen(dst);
	j = 0;
	if (dstsize <= i)
		return (ft_strlen(src) + dstsize);
	while (i < dstsize - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (to_return);
}
