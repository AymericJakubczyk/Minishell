/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:02:11 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/11 18:24:21 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	size_of_parse(t_entry *entry)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (entry[i].c != '\0')
	{
		if (entry[i].type == WHITESPACE && entry[i].context == NO_QUOTE)
		{
			while (entry[i].c != '\0' && entry[i].type == WHITESPACE && \
					entry[i].context == NO_QUOTE)
				i++;
		}
		else
		{
			nbr++;
			i += go_to_end_block(&entry[i]);
		}
	}
	return (nbr);
}

void	set_type_utils(int type1, int type2, int *i, t_parse *parse)
{
	parse[*i].type = type1;
	parse[*i + 1].type = type2;
	*i += 2;
}

void	set_type_utils2(int type, int *cmd, int *i, t_parse *parse)
{
	parse[*i].type = type;
	if (*cmd == 0)
		*cmd = 1;
	else
		*cmd = 0;
	*i += 1;
}

void	free_all_parse(t_parse *parse)
{
	int	i;

	i = 0;
	while (parse[i].str)
	{
		free(parse[i].str);
		i++;
	}
	free(parse);
}
