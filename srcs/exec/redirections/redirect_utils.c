/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 06:19:27 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 06:19:31 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_quote(char *quote, char c, int *i)
{
	*quote = c;
	*i += 1;
}

int	is_env_var(char *str, char quote)
{
	if (quote != '\'' && str[1] && \
		(ft_isalnum(str[1]) || str[1] == '_' || str[1] == '?'))
		return (1);
	return (0);
}

char	*get_name_var(char *str, int *i)
{
	char	*name;

	name = ft_strdup("");
	*i += 1;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		name = ft_strjoin2(name, char_to_str(str[*i]));
		*i += 1;
	}
	return (name);
}

int	last_redir(t_parse *parse, int mode)
{
	int	type_redirect;
	int	i;

	type_redirect = -1;
	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (mode == IN && (parse[i].type == REDIRECT_IN \
			|| parse[i].type == HEREDOC))
			type_redirect = parse[i].type;
		if (mode == OUT && (parse[i].type == REDIRECT_OUT \
		|| parse[i].type == APPEND))
			type_redirect = parse[i].type;
		i++;
	}
	return (type_redirect);
}

char	*get_last_file(t_parse *parse, t_list **my_env, int mode)
{
	int	i;

	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
		i++;
	while (i >= 0)
	{
		if (mode == IN && parse[i].type == INFILE)
			return (expand_redirect(parse[i], my_env));
		if (mode == OUT && parse[i].type == OUTFILE)
			return (expand_redirect(parse[i], my_env));
		i--;
	}
	return (NULL);
}
