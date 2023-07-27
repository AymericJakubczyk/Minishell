/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:06:16 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/27 01:03:57 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// # include "struct.h"

enum e_mode {
	IN,
	OUT
};

// execution.c
int		execution(t_parse *parse, t_list **my_env, t_exec *data);
int		how_many_cmds(t_parse *parse);
void	ex_child(t_parse *parse, t_list **env, int runner, t_exec *data);

// exec_utils.c
void	init_file(t_exec *data);
int		is_directory(char *cmd, t_list **env, t_exec *data);
int		slash_in(char *str);
int		find_arg(t_parse *parse);

//get_path_utils.c
char	*get_path(char *cmd, t_list **env, t_exec *data);

//do_heredoc.c
int		do_heredoc(t_parse *parse, t_exec *data, t_list **my_env);

//get_heredoc.c
void	get_heredoc(t_exec *data, t_list **my_env);

//heredoc_utils.c
int		quote_in(char *str);
char	*lim_without_quote(char *str);
char	*ft_get_str_hd(t_parse *parse, t_exec *my_struct, int num_cmd);
int		heredoc_in(t_parse *parse);
char	*next_expand_heredoc(t_list **my_env, char *str_expanded, \
		char *str, int i);

//expand_heredoc.c
char	*expand_heredoc(char *str, t_list **my_env);

//exec_with_forks.c
void	exec_with_forks(t_parse *parse, t_list **my_env, t_exec *data);

//exec_cmd.c
void	exec_cmd(t_parse *parse, int num_cmd, t_list **my_env, t_exec *data);

//exec_fork_utils.c
int		last_redir(t_parse *parse, int mode);
char	*get_last_file(t_parse *parse, t_list **my_env, int mode);
char	**get_arg(t_parse *parse);

//do_redirect.c
int		redirect_in_cmd(t_parse *parse, int mode);
void	do_classique_pipe(int num_cmd, t_exec *data, int mode);
void	do_redirect_in(t_parse *parse, t_list **my_env, t_exec *data, \
		int num_cmd);
void	do_redirect_out(t_parse *parse, t_list **my_env, t_exec *data);

//check_redirect.c
int		check_all_redirect(t_parse *parse, t_list **my_env, t_exec *data);
int		check_all_redirect_without_fork(t_parse *parse, t_list **my_env);

//expand_redirect.c
char	*expand_redirect(t_parse parse, t_list **my_env);

//size_expand_redir.c
int		size_expanded_redir(char *str, t_list **my_env);

//fill_expanded_redir.c
void	fill_expanded_redir(t_entry *entry, char *str, t_list **my_env);

//redirect_utils.c
void	set_quote(char *quote, char c, int *i);
int		is_env_var(char *str, char quote);
char	*get_name_var(char *str, int *i);

//single_cmd.c
void	single_cmd(t_parse *parse, t_list **my_env, t_exec *data);

//single_cmd_utils.c
void	double_close(int *file1, int *file2);
void	verif_status(int status);

//start_exec.c
int		which_builtin(t_parse *parse, int runner);

//exec_fork_utils.c
int		get_start_cmd(t_parse *parse, int num_cmd);

//signals.c
void	signal_heredoc(int sig);

void	handler_fork(int sig);
void	handler_fork_slash(int sig);

#endif