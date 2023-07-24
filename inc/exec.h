/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:06:16 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/24 17:25:11 by cprojean         ###   ########.fr       */
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
void	execution(t_parse *parse, t_list **my_env, t_exec *data);
int		how_many_cmds(t_parse *parse);
void	ex_child(t_parse *parse, t_list **env, int runner, t_exec *data);

//do_heredoc.c
void	do_heredoc(t_parse *parse, t_exec *my_struct, t_list **my_env);

//heredoc_utils.c
int		quote_in(char *str);
char	*limiter_without_quote(char *str);
char	*ft_get_str_hd(t_parse *parse, t_exec *my_struct, int num_cmd);
int		heredoc_in(t_parse *parse);

//expand_heredoc.c
char	*expand_heredoc(char *str, t_list **my_env);

//exec_with_forks.c
void	exec_with_forks(t_parse *parse, t_list **my_env, t_exec *data);

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

//exec_utils.c
char	*get_path(char *cmd, t_list **env, t_parse *parse);
void	init_file(t_exec *data);

//check_redirect.c
int		check_all_redirect(t_parse *parse, t_list **my_env, t_exec *data);
int		check_all_redirect_without_fork(t_parse *parse, t_list **my_env);
int		check_redirect(t_parse parse, t_list **my_env, int in);
char	*expand_redirect(t_parse parse, t_list **my_env);

//single_cmd.c
void	single_cmd(t_parse *parse, t_list **my_env, t_exec *data);
void	handle_forked_single_builtin(t_parse *parse, \
		t_list **my_env, int runner, t_exec *data);
void	handle_single_builtin(t_parse *parse \
		, t_list **my_env, int runner, t_exec *data);
void	exec_single_cmd(t_parse *parse, t_list **env, int runner, t_exec *data);

//single_cmd_utils.c
int		dup_in(t_parse *parse, int runner, t_exec *data, t_list **my_env);
int		dup_out(t_parse *parse, int runner, t_list **my_env);
void	double_close(int *file1, int *file2);
void	restore_dup(int file[2], t_exec *data, int *pipe);
void	single_cmd_execution(t_parse *parse, t_list **my_env, t_exec *data);

//start_exec.c
int		which_builtin(t_parse *parse, int runner);

//check_redirects
int		get_ind_last_char(t_entry *entry);

//exec_fork_utils.c
int		do_builtin(t_parse *parse, t_list **my_env, char **arg, t_exec *data);
int		get_start_cmd(t_parse *parse, int num_cmd);

void	handler_fork(int sig);
void	handler_fork_slash(int sig);

#endif