/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:00:49 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/11/19 18:27:47 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && len == 0)
		return (0);
	if (ft_strlen(s2) == 0)
		return ((char *) s1);
	while (s1[i] != '\0' && i < len)
	{
		while (s1[i + j] == s2[j] && s1[i + j] && s2[j] && i + j < len)
			j++;
		if (s2[j] == '\0')
			return ((char *) &s1[i]);
		j = 0;
		i++;
	}
	return (0);
}
