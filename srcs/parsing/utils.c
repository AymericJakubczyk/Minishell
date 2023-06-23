/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:41:21 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/22 16:00:09 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*mem;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (ft_free(s1, s2), NULL);
	mem = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (mem == 0)
		return (ft_free(s1, s2), NULL);
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
	return (ft_free(s1, s2), mem);
}

char	*ft_strjoin3(char *s1, char *s2)
{
	char	*mem;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (free(s1), NULL);
	mem = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (mem == 0)
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
		j++;
		i++;
	}
	mem[j] = '\0';
	return (free(s1), mem);
}

char	*ft_strjoin4(char *s1, char *s2)
{
	char	*mem;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (free(s2), NULL);
	mem = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (mem == 0)
		return (free(s2), NULL);
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
	return (free(s2), mem);
}

int	ft_strcmp(char *s1, char*s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '\n' && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	if (s1[i] == '\n')
		return (s2[i]);
	return (s1[i] - s2[i]);
}
