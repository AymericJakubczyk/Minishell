/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:36:50 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/23 13:27:12 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H

typedef struct s_garb
{
	void	*malloc;
	struct s_garb	*next;
}	t_garb;

void	ft_garb_addback(t_garb **garb, t_garb *trash);
t_garb	*ft_garb_last(t_garb *garb);
void	ft_garb_clear(t_garb **garb);
t_garb	*ft_garb_new(void *addr);

#endif