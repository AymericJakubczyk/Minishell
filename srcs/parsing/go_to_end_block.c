/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_end_block.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 04:26:31 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/26 04:26:44 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_to_end_block(t_entry *entry)
{
	int	i;

	i = 0;
	if (entry[i].type == CHEV_IN && entry[i].context == NO_QUOTE)
	{
		i++;
		if (entry[i].type == CHEV_IN && entry[i].context == NO_QUOTE)
			return (2);
		return (i);
	}
	if (entry[i].type == CHEV_OUT && entry[i].context == NO_QUOTE)
	{
		i++;
		if (entry[i].type == CHEV_OUT && entry[i].context == NO_QUOTE)
			return (2);
		return (i);
	}
	while (entry[i].c != '\0' && !(entry[i].type == WHITESPACE && \
			entry[i].context == NO_QUOTE) && !(entry[i].context == \
			NO_QUOTE && (entry[i].type == CHEV_IN || entry[i].type == \
			CHEV_OUT || entry[i].type == PIPE)))
		i += 1;
	if (i == 0)
		return (1);
	return (i);
}
