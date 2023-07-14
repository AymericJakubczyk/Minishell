/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:40:43 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/14 04:15:55 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//Builtins.c
char		*ft_pwd();
void		ft_echo(t_parse *parse);
void		ft_env(t_list **env);
void		ft_cd(t_list **my_env, t_parse *parse);
int			ft_exit(char *array);


//Export.c & his utils
void	ft_export(t_list **my_env, t_parse *parse);
int		is_allready_export(t_list **my_env, char *str);
int		ft_equal_size(char *str);
char	*skip_equal(char *str);
char	*ft_str_skip_add(char *str);
int		is_addition(char *str);

//ft_getenv.c
char	*ft_getenv(t_list **my_env, char *get_me, int do_free);
void	ft_dup_env(char **env, t_list **my_env);

//Unset.c
void	ft_unset(t_list **my_env, t_parse *parse);

#endif