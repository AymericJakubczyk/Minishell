/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:52:05 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/18 13:17:50 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// # include "struct.h"

enum e_types {
	CHAR,
	WHITESPACE,
	CHEV_IN,
	CHEV_OUT,
	PIPE,
	S_QUOTE,
	D_QUOTE,
	STRING,
	EXPAND,
	VOID
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
//from 0 to 9

//utils.c
void	ft_free(char *s1, char *s2);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strjoin3(char *s1, char *s2);
char	*ft_strjoin4(char *s1, char *s2);
int		ft_strcmp(char *s1, char*s2);

//get_prompt.c
char	*ft_get_prompt(t_list **my_env);

//parse_and_exec.c
void	parse_and_exec(char *str, t_list **my_env, t_exec *data);

//check_syntax.c
int		check_syntax_quote(char *str);

//first_parse.c
void	init_entry(t_entry *entry, char *str);

//second_parse.c
int		colapse_all(t_entry *entry, t_parse *parse);
int		go_to_end_block(t_entry *entry);

//parse_errors.c
int		check_parse(t_parse *input);

//next_parse_errors.c
int		next_parse_check(t_parse *input);

//parse_utils.c
char	*char_to_str(char c);
int		size_of_parse(t_entry *entry);
void	set_type_utils(int type, int *i, t_parse *parse);
void	set_type_utils2(int type, int *cmd, int *i, t_parse *parse);
void	free_all_parse(t_parse *parse);

//expand.c
void	expand(t_entry *entry, t_entry **new_entry, t_list **my_env);

//get_expand_size.c
int		get_expand_size(t_entry *entry, t_list **my_env);

//fill_expand.c
int		fill_expand(t_entry *entry, t_entry *new_entry, t_list **my_env);

//expand_utils.c
char	*get_name_env(t_entry *entry, int *i);
void	copy_entry_value(t_entry *entry, t_entry *new_entry, int *i, int *j);
int		good_char_env(t_entry *entry, int i);
int		check_tild(t_entry *entry, int i);
void	fill_value_env(t_entry *new_entry, int context, char *value_env, \
	int *j);

//print.c
void	print_parse(t_parse *parse);









void	print_all(char **str);
void	free_all(char **str);
void	handler(int sig);

#endif