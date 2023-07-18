/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:40:43 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/18 15:53:47 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//Builtins.c
char	*ft_pwd(void);
void	ft_echo(t_parse *parse);
void	ft_env(t_list **env);
void	ft_cd(t_list **my_env, t_parse *parse);
int		ft_exit(char *array);

//Bultins utils
void	do_ft_export(t_list **my_env, char *str);
void	next_cd(t_list **my_env, char *str);
int		equal(char *str);
char	*add_quotes(char *str);

//Export.c & his utils
void	ft_export(t_list **my_env, t_parse *parse);
int		is_allready_export(t_list **my_env, char *str);
int		ft_equal_size(char *str);
char	*skip_equal(char *str);
char	*ft_str_skip_add(char *str);
int		is_addition(char *str);
void	check_export_type(t_list **my_env, t_parse *parse, int runner, t_list *tmp);
void	export_again(t_list **my_env, char *str);
void	add_to_existing_one(t_list *tmp, char *str);
int		is_alpha_export(char *str);

//ft_getenv.c
char	*ft_getenv(t_list **my_env, char *get_me, int do_free);
void	ft_dup_env(char **env, t_list **my_env);
void	ft_create_env(t_list **my_env);

//Unset.c
void	ft_unset(t_list **my_env, t_parse *parse);
int		is_alpha(char *str);

#endif