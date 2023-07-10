/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:06:16 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/28 19:19:34 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// # include "struct.h"

// execution.c
void	execution(t_parse *parse, t_list **my_env, t_exec *data);
int	how_many_cmds(t_parse *parse);
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

//exec_utils.c
char	*get_path(char *cmd, t_list **env);
void	init_file(int *fd1, int *fd2, t_exec *data);

//check_redirect.c
int	check_redirect(t_parse parse, t_list **my_env, char **expanded, int in);

//single_cmd.c
void	single_cmd(t_parse *parse, t_list **my_env, t_exec *data);

//single_cmd_utils.c
int	dup_in(t_parse *parse, int runner, int mode, int *pipe, t_exec *data);
int	dup_out(t_parse *parse, int runner);
void	double_close(int file1, int file2);
void	restore_dup(int file[2], t_exec *data, int *pipe);
void	single_cmd_execution(t_parse *parse, t_list **my_env, t_exec *data);



#endif