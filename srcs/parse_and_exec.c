/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:24:28 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/10 13:26:12 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_entry(t_entry *entry);
void	print_parse(t_parse *parse);
void	free_all_parse(t_parse *parse);
void	init_entry(t_entry *entry, char *str);
void	which_type(t_entry *entry, char c);

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
	check_parse(parse);
	// type_parse(parse);
	//expand();
	//exec();
	free_all_parse(parse);
}

void	print_entry(t_entry *entry)
{
	int	i;

	i = 0;
	ft_printf("print entry : \n");
	while (entry[i].c != '\0')
	{
		ft_printf("%c | type : %i | context : %i\n", entry[i].c, entry[i].type, entry[i].context);
		i++;
	}
}

void	print_parse(t_parse *parse)
{
	int	i;

	i = 0;
	ft_printf("print parse : \n");
	while (parse[i].str)
	{
		ft_printf("%s\n", parse[i].str);
		i++;
	}
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
