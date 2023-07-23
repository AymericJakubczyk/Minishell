/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:16:31 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/24 00:00:34 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERROR_1 "syntax error near unexpected token 'newline'"
# define ERROR_2 "syntax error near unexpected token '>>'"
# define ERROR_3 "syntax error near unexpected token '>'"
# define ERROR_4 "syntax error near unexpected token '<<'"
# define ERROR_5 "syntax error near unexpected token '<'"
# define ERROR_6 "syntax error near unexpected token '||'"
# define ERROR_7 "syntax error near unexpected token '|'"
# define ERROR_8 "syntax error near unexpected token '&&'"
# define ERROR_9 "syntax error near unexpected token '('"
# define ERROR_10 "syntax error near unexpected token ')'"
# define ERROR_11 "is a directory"
# define ERROR_12 "command not found"
# define ERROR_13 "no such file or directory"
# define ERROR_14 "filename argument required"
# define ERROR_15 "Permission denied"
# define ERROR_16 "not a valid identifier"
# define ERROR_17 "invalid option"
# define ERROR_18 "numeric argument required"
# define ERROR_19 "parse error near '\'"
# define ERROR_20 "parse error near '|'"
# define ERROR_22 ": not a valid identifier"
# define ERROR_23 ": too many arguments"
# define ERROR_42 "help allocation broke"
# define ERROR_24 ": is a directory"
# define ERROR_99 "tu crois aller ou comme ca"

void	ft_error(const char *error, char *problem, int nbrerror);
#endif