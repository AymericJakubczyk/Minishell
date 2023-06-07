/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:24:28 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/07 07:46:50 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_entry(t_entry *entry)
{
	int	i;

	i = 0;
	ft_printf("print entry : \n");
	while (entry[i].c != 0)
	{
		ft_printf("%c : %i\n", entry[i].c, entry[i].type);
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
		ft_printf("%s : %i\n", parse[i].str, parse[i].type);
		i++;
	}
}

void free_all_parse(t_parse *parse)
{
	int	i;

	i = 0;
	while (parse[i].str)
	{
		free(parse[i].str);
		i++;
	}
	free(parse);
	exit(1); //mettre valeur d'exit en parametre selon les cas ???
}

void	parse_and_exec(char *str)
{
	t_entry	*entry;
	t_parse	*parse;

	//entry = malloc(sizeof(t_entry) * (ft_strlen(str) + 1));
	entry = ft_calloc(sizeof(t_entry), ft_strlen(str) + 1);
	if (!entry)
		exit(1);
	init_entry(entry, str);
	print_entry(entry);
	ft_printf("nbr mots : %d\n", size_of_parse(entry));
	//check_syntax(entry);
	parse = malloc(sizeof(t_parse) * (size_of_parse(entry) + 1));
	if (!parse)
	{
		free(entry);
		exit(1);	
	}
	colapse_all_string(entry, parse, size_of_parse(entry));
	print_parse(parse);
	//check_quote();
	//expand();
	//exec();
	free(entry);
	free_all_parse(parse);
}

void init_entry(t_entry *entry, char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		entry[i].c = str[i];
		which_type(&entry[i], str[i]);
		i++;
	}
	entry[i].c = 0;
}

void	which_type(t_entry *entry, char c)
{
	if (c == ' ')
		entry->type = SPACES;
	else if (c == '<')
		entry->type = CHEV_IN;
	else if (c == '>')
		entry->type = CHEV_OUT;
	else if (c == '|')
		entry->type = PIPE;
	else if (c == '\'')
		entry->type = S_QUOTE;
	else if (c == '\"')
		entry->type = D_QUOTE;
	else
		entry->type = CHAR;
}
