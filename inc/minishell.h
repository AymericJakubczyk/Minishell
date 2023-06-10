/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:02:11 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/10 16:30:16 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "error.h"

enum e_types {
	CHAR,
	WHITESPACE,
	CHEV_IN,
	CHEV_OUT,
	PIPE,
	S_QUOTE,
	D_QUOTE,
	STRING,
};

enum e_context {
	NO_QUOTE,
	SI_QUOTE,
	DO_QUOTE
};

enum e_species {
	INFILE,
	OUTFILE,
	PIPEE,
	REDIRECT_IN,
	HEREDOC,
	LIMITER,
	REDIRECT_OUT,
	APPEND,
	COMMAND,
	CMD_ARG
};

typedef struct s_entry
{
	char	c;
	int		type;
	int		context;
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