/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:16:31 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/08 15:49:48 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERROR_1 "syntax error near unexpected token 'newline'\n"
# define ERROR_2 "syntax error near unexpected token '>>'\n"
# define ERROR_3 "syntax error near unexpected token '>'\n"
# define ERROR_4 "syntax error near unexpected token '<<'\n"
# define ERROR_5 "syntax error near unexpected token '<'\n"
# define ERROR_6 "syntax error near unexpected token '||'\n"
# define ERROR_7 "syntax error near unexpected token '|'\n"
# define ERROR_8 "syntax error near unexpected token '&&'\n"
# define ERROR_9 "syntax error near unexpected token '('\n"
# define ERROR_10 "syntax error near unexpected token ')'\n"
# define ERROR_11 "is a directory\n"
# define ERROR_12 "command not found\n"
# define ERROR_13 "no such file or directory\n"
# define ERROR_14 "filename argument required\n"
# define ERROR_15 "Permission denied\n"
# define ERROR_16 "not a valid identifier\n"
# define ERROR_17 "invalid option\n"
# define ERROR_18 "numeric argument required\n"

void	ft_error(const char *error, char *problem);
#endif