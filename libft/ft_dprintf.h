/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:57:18 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/23 00:53:45 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_dprintf(const char *str, ...);
void	ft_dputchar(char c, ssize_t *count);
void	ft_dputnbr(int n, ssize_t *count);
void	ft_dputunbr(unsigned int n, ssize_t *count);
void	ft_dput_hexa(unsigned int nbr, char *base, ssize_t *count);
void	ft_dputptr_hexa(size_t nbr, ssize_t *count);
void	ft_dputstr(char *str, ssize_t *count);
size_t	dafter(size_t i, const char *str, va_list va, ssize_t *count);

#endif
