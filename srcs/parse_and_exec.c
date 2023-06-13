/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:24:28 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/13 10:26:16 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_and_exec(char *str)
{
	t_entry	*entry;
	t_parse	*parse;

	check_syntax_quote(str);
	entry = ft_calloc(sizeof(t_entry), ft_strlen(str) + 1);
	if (!entry)
		exit(1);
	init_entry(entry, str);
	parse = malloc(sizeof(t_parse) * (size_of_parse(entry) + 1));
	if (!parse)
	{
		free(entry);
		exit(1);
	}
	colapse_all(entry, parse);
	free(entry);
	print_parse(parse);
	//expand();
	//exec();
	free_all_parse(parse);
}
