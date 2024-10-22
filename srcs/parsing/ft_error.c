/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:43:46 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/27 15:34:36 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"

void	ft_error(const char *error, char *problem, int nbrerror)
{
	if (nbrerror)
		g_errno = nbrerror;
	if (problem != NULL)
		ft_print_error("(s)Hell : ", error, problem);
	else
		ft_print_error("(s)Hell : ", error, NULL);
}

void	ft_print_error(char *prompt, const char *error, char *problem)
{
	char	*str;

	str = ft_strdup("");
	str = ft_strjoin3(str, prompt);
	if (problem)
	{
		str = ft_strjoin3(str, " ");
		str = ft_strjoin3(str, problem);
	}
	if (error)
	{
		str = ft_strjoin3(str, " ");
		str = ft_strjoin3(str, (char *)error);
	}
	str = ft_strjoin3(str, "\n");
	write(2, str, ft_strlen(str));
	free(str);
}
