/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:09:34 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/11/19 18:32:45 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mem;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	mem = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (mem == 0)
		return (0);
	i = 0;
	while (s1[i])
	{
		mem[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i])
	{
		mem[j] = s2[i];
		j++;
		i++;
	}
	mem[j] = '\0';
	return (mem);
}
