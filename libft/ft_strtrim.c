/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:46:20 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/11/23 18:09:27 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char const *set, char c)
{
	int	i;

	if (!set)
		return (0);
	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	start;
	int	len;

	if (!s1)
		return (0);
	i = 0;
	while (s1[i] != '\0' && is_in_set(set, s1[i]))
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (i >= 0 && is_in_set(set, s1[i]))
		i--;
	len = i + 1 - start;
	return (ft_substr(s1, start, len));
}
