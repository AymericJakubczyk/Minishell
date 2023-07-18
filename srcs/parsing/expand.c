/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:13:46 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/18 15:36:10 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_entry *entry, t_entry **new_entry, t_list **my_env)
{
	int	size;

	size = get_expand_size(entry, my_env);
	if (size == -1)
		return ;
	*new_entry = malloc(sizeof(t_entry) * (size + 1));
	if (!new_entry)
	{
		ft_error(ERROR_42, NULL, 12);
		return ;
	}
	fill_expand(entry, *new_entry, my_env);
}
