/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:29:41 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/12 17:43:10 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content, int type)
{
	t_list	*new_lst;

	new_lst = malloc (sizeof(t_list));
	if (new_lst == 0)
		return (0);
	new_lst->content = content;
	new_lst->type = type;
	new_lst->next = 0;
	return (new_lst);
}
