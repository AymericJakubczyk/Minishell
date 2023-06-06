/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:52:45 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/11/30 20:54:43 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nbr_parts(const char *s, char c);
static int	set_fill_tab(char **tab, int i_part, const char *s, char c);
static void	free_all_tab(char **tab, int i_part);

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	ssize_t	i_tmp;
	int		i_part;

	if (s == 0)
		return (0);
	i = 0;
	i_part = 0;
	tab = malloc(sizeof(char *) * (get_nbr_parts(s, c) + 1));
	if (tab == 0)
		return (0);
	while (s[i] == c)
		i++;
	while (i < ft_strlen(s))
	{
		i_tmp = set_fill_tab(tab, i_part, &s[i], c);
		if (i_tmp == -1)
			return (0);
		i += i_tmp;
		i_part++;
	}
	tab[i_part] = 0;
	return (tab);
}

static void	free_all_tab(char **tab, int i_part)
{
	while (i_part >= 0)
	{
		free(tab[i_part]);
		i_part--;
	}
	free(tab);
}

static int	get_nbr_parts(const char *s, char c)
{
	int	i;
	int	nbr_parts;

	nbr_parts = 0;
	i = 0;
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			nbr_parts++;
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			nbr_parts--;
		else
			i++;
	}
	return (nbr_parts + 1);
}

static int	set_fill_tab(char **tab, int i_part, const char *s, char c)
{
	int	len_part;

	len_part = 0;
	while (s[len_part] != c && s[len_part] != '\0')
		len_part++;
	tab[i_part] = malloc(sizeof(char) * (len_part + 1));
	if (tab[i_part] == 0)
	{
		free_all_tab(tab, i_part);
		return (-1);
	}
	ft_strlcpy(tab[i_part], s, len_part + 1);
	while (s[len_part] && s[len_part] == c)
		len_part++;
	return (len_part);
}
