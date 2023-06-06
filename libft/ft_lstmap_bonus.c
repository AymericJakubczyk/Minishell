/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:29:33 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/11/22 13:29:55 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem_to_return;
	t_list	*new;
	char	*str;

	elem_to_return = 0;
	if (lst == 0 || f == 0 || del == 0)
		return (0);
	while (lst != 0)
	{
		str = f(lst->content);
		new = ft_lstnew(str);
		if (new == 0)
		{
			del(str);
			ft_lstclear(&elem_to_return, del);
			return (0);
		}
		ft_lstadd_back(&elem_to_return, new);
		lst = lst -> next;
	}
	return (elem_to_return);
}
