/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:28:32 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/11/22 13:29:55 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*elem_before;
	t_list	*current_elem;

	if (lst == 0 || *lst == 0 || del == 0)
		return ;
	current_elem = *lst;
	elem_before = *lst;
	while (current_elem)
	{
		elem_before = current_elem;
		current_elem = elem_before->next;
		ft_lstdelone(elem_before, del);
	}
	*lst = NULL;
}
