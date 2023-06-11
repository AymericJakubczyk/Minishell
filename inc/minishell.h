/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:02:11 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/11 18:56:00 by cprojean         ###   ########.fr       */
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
	INFILE,			//0
	OUTFILE,		//1
	PIPEE,			//2
	REDIRECT_IN,	//3
	HEREDOC,		//4
	LIMITER,		//5
	REDIRECT_OUT,	//6
	APPEND,			//7
	COMMAND,		//8
	CMD_ARG,		//9
	EXPEND			//10
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

//print.c


//get_prompt.c
char	*ft_get_prompt(void);

//parse_and_exec.c
void	parse_and_exec(char *str);

//check_syntax.c
void	check_syntax_quote(char *str);

//first_parse.c
void	init_entry(t_entry *entry, char *str);

//second_parse.c
void	colapse_all(t_entry *entry, t_parse *parse);
int		go_to_end_block(t_entry *entry);

//parse_errors.c
int	check_parse(t_parse *input);

//next_parse_errors.c
int	next_parse_check(t_parse *input);

//parse_utils.c
char	*char_to_str(char c);
int		size_of_parse(t_entry *entry);
void	set_type_utils(int type1, int type2, int *i, t_parse *parse);
void	set_type_utils2(int type, int *cmd, int *i, t_parse *parse);
void	free_all_parse(t_parse *parse);

#endif