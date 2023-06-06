/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:48:21 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/11/19 18:27:47 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mem;
	int		i;
	size_t	j;

	if (s == 0 || ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) > len)
		mem = malloc(sizeof(char) * (len + 1));
	else
		mem = malloc(sizeof(char) * (ft_strlen(&s[start]) + 1));
	if (mem == 0)
		return (0);
	i = start;
	j = 0;
	while (s[i] != '\0' && j < len)
	{
		mem[j] = s[i];
		i++;
		j++;
	}
	mem[j] = '\0';
	return (mem);
}
