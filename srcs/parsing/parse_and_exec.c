/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:24:28 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/21 17:06:14 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void conver_parse_to_list(t_parse *parse, t_list **list);
void print_list(t_list *list);

void	parse_and_exec(char *str)
{
	t_entry	*entry;
	t_parse	*parse;
	t_list *list;

	list = NULL;
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
	//print_parse(parse);
	conver_parse_to_list(parse, &list);
	print_list(list);
	expand(list);
	print_list(list);
	//exec();
	free_all_parse(parse);
}


void conver_parse_to_list(t_parse *parse, t_list **list)
{
	int i;
	
	i = 0;
	while (parse[i].str)
	{
		ft_lstadd_back(list, ft_lstnew(parse[i].str, parse[i].type));
		i++;
	}
}

void print_list(t_list *list)
{
	ft_printf("LIST :\n");
	while (list)
	{
		ft_printf("%s : %d\n", list->content, list->type);
		list = list->next;
	}
}
