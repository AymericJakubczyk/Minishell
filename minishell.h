/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:02:11 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/07 06:13:16 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"

enum e_types {
	CHAR,
	SPACES,
	CHEV_IN,
	CHEV_OUT,
	PIPE,
	S_QUOTE,
	D_QUOTE,
	STRING,
};

typedef struct s_entry
{
	char	c;
	int		type;
}	t_entry;

typedef struct s_parse
{
	char	*str;
	int		type;
}	t_parse;

//utils.c
void	ft_free(char *s1, char *s2);
char	*ft_strjoin2(char *s1, char *s2);

//get_prompt.c
char	*ft_get_prompt(void);

#endif