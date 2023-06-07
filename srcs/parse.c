/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:55:37 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/07 07:59:37 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_of_parse(t_entry *entry)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	//ft_printf("PARSE\n");
	while (entry[i].c != '\0')
	{
		//ft_printf("%c : %d CHAR : %d\n", entry[i].c, entry[i].type, CHAR);
		if (entry[i].type == CHAR)
		{
			while (entry[i].type == CHAR && entry[i].c != '\0')
				i++;
		}
		else
			i++;
		nbr++;
	}
	//ft_printf("nbr mots : %d\n", nbr);
	return (nbr);
}

char	*char_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = 0;
	return (str);
}

char	*colapse_letter(t_entry *entry, int i)
{
	char	*str;

	str = ft_strdup("");
	//ft_printf("before mot : \n");
	while (entry[i].type == CHAR && entry[i].c != '\0')
	{
		//ft_printf("%s", &entry[i].c);
		str = ft_strjoin2(str, char_to_str(entry[i].c));
		i++;
	}
	//ft_printf("\nmot %s\n", str);
	return (str);
}




void	colapse_all_string(t_entry *entry, t_parse *parse, int size_of_parse)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (entry[i].c != '\0')
	{
		if (entry[i].type == CHAR)
		{
			str = colapse_letter(entry, i);
			parse[j].str = str;
			parse[j].type = STRING;
			//i += ft_strlen(str);
		}
		else
		{
			parse[j].str = char_to_str(entry[i].c);
			parse[j].type = entry[i].type;
			//i++;
		}
		if (!str)
			free_all_parse(parse);
		i += ft_strlen(parse[j].str)
		j++;
	}
	parse[j].str = NULL;
}

// expand();