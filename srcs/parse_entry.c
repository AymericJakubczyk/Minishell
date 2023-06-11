/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:47:22 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/11 15:52:43 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*char_to_str(char c);
char	*get_str(t_entry *entry, int *i, int j);
int		set_type(t_parse *parse);


void	colapse_all(t_entry *entry, t_parse *parse)
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
			parse[nbr].str = get_str(entry, &i, go_to_end_block(&entry[i]));
			nbr++;
		}
	}
	parse[nbr].str = NULL;
}

int	set_type(t_parse *parse)
{
	int i;
	int cmd;

	cmd = 0;
	i = 0;
	while (parse[i].str)
	{
		if (parse[i].str[0] == '<' && ft_strlen(parse[i].str) == 1)
		{
			parse[i].type = REDIRECT_IN;
			i++;
			if (parse[i].str)
			{
				parse[i].type = INFILE;
				i++;
			}
			else
				return (ft_printf("syntax error\n"), 0);
		}
	}
}

char	*get_str(t_entry *entry, int *i, int j)
{
	char	*str;
	int		runner;

	runner = 0;
	str = ft_strdup("");
	while (runner < j)
	{
		str = ft_strjoin2(str, char_to_str(entry[*i].c));
		*i += 1;
		runner++;
	}
	return (str);
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