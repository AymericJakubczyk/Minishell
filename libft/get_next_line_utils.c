/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:33:06 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/12/01 15:44:06 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

ssize_t	backslash(char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*mem;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	mem = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!mem)
		return (free(s1), NULL);
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
		i++;
		j++;
	}
	mem[j] = '\0';
	return (free(s1), mem);
}

void	setup_buf(char *buf, size_t i)
{
	size_t	j;

	j = 0;
	i++;
	while (buf[i] && i < BUFFER_SIZE)
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	buf[j] = '\0';
}
