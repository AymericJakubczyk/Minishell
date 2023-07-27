/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:40:43 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/27 01:52:09 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//Builtins.c
void		ft_echo(t_parse *parse);
void		ft_env(t_list **env, t_parse *parse);
char		*ft_pwd(int mode);

//Bultins utils
char		*add_quotes(char *str);
int			equal(char *str);
int			check_dir(char *str);
void		do_ft_export(t_list **my_env, char *str);

//Export.c
void		ft_export(t_list **my_env, t_parse *parse);
void		add_to_existing_one(t_list *tmp, char *str);
void		export_again(t_list **my_env, char *str);
void		ft_print_export(t_list **my_env);
char		**dup_env_sort(char **array, t_list **my_env);

//export_utils.c
int			is_allready_export(t_list **my_env, char *str);
int			ft_equal_size(char *str);
char		*skip_equal(char *str);
char		*ft_str_skip_add(char *str);
int			is_addition(char *str);

//export_utils2.c
void		check_export_type(t_list **my_env \
			, t_parse *parse, int runner, t_list *tmp);
void		next_check_export_type(t_list **my_env, t_parse *parse, \
			int runner);
int			ft_equal_ind(char *str);
void		print_it(char **array, t_list **my_env);
int			is_two_dash(char *str);

//ft_atoll.c
long long	ft_atoll(const char *str, t_list **my_env, t_exec *data);
long long	is_overflow(const char *str, int sign);

//ft_exit.c
void		ft_exit(t_parse *parse, t_list **my_env, char **arg, t_exec *data);
void		free_minishell(t_exec *data, t_list **my_env);

//ft_exit_utils.c
int			do_overflow(char *str);
int			count_args(t_parse *parse);
int			is_num(char *str);

//ft_cd.c
void		ft_cd(t_list **my_env, t_parse *parse);
void		next_cd(t_list **my_env, char *str, char *oldpwd);
void		cd_errors(int *count, int *flag, t_parse *parse);

//ft_getenv.c
char		*ft_getenv(t_list **my_env, char *get_me, int do_free);
void		ft_dup_env(char **env, t_list **my_env);
void		ft_create_env(t_list **my_env);

//Unset.c
void		ft_unset(t_list **my_env, t_parse *parse);
void		unset_cmd(t_list **my_env, t_parse *parse, int index, int *count);
void		first_var_unset(t_list **my_env);
int			is_alpha(char *str);
int			is_alpha_export(char *str);

#endif