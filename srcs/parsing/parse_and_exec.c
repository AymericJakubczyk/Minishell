/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:24:28 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/23 23:22:09 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	conver_parse_to_list(t_parse *parse, t_list **list);
void	print_list(t_list *list);
int		convert_entry_to_parse(t_entry *entry, t_parse **parse);

void	parse_and_exec(char *str, t_list **my_env, t_exec *data)
{
	t_entry	*entry;
	t_entry	*new_entry;
	t_parse	*parse;

	new_entry = NULL;
	parse = NULL;
	if (!check_syntax_quote(str))
		return ;
	// ft_printf("entry malloc size : %d\n", ft_strlen(str) + 1);
	entry = malloc(sizeof(t_entry) * (ft_strlen(str) + 1));
	if (!entry)
	{
		ft_error(ERROR_42, NULL, 12);
		return ;
	}
	init_entry(entry, str);
	if (!convert_entry_to_parse(entry, &parse))
		return ;
	free_all_parse(parse);
	expand(entry, &new_entry, my_env);
	free(entry);
	if (!convert_entry_to_parse(new_entry, &parse))
		return ;
	free(new_entry);
	// print_parse(parse);
	execution(parse, my_env, data);
	// print_all(data->all_limiter);
	// print_all(data->str_heredoc);
	if (data->all_limiter)
		free(data->all_limiter);
	free_all(data->str_heredoc);
	free_all_parse(parse);
}

int	convert_entry_to_parse(t_entry *entry, t_parse **parse)
{
	*parse = malloc(sizeof(t_parse) * (size_of_parse(entry) + 1));
	if (!*parse)
	{
		ft_error(ERROR_42, NULL, 12);
		free(entry);
		return (0);
	}
	if (colapse_all(entry, *parse) == 0)
	{
		free(entry);
		free_all_parse(*parse);
		return (0);
	}
	// ft_printf("IM HERE HERE HERE\n");
	return (1);
}

//TO REMOVE
void	conver_parse_to_list(t_parse *parse, t_list **list)
{
	int	i;

	i = 0;
	while (parse[i].str)
	{
		ft_lstadd_back(list, ft_lstnew(parse[i].str, parse[i].type));
		i++;
	}
}

void	print_list(t_list *list)
{
	ft_printf("LIST :\n");
	while (list)
	{
		ft_printf("%s : %d\n", list->content, list->type);
		list = list->next;
	}
}
