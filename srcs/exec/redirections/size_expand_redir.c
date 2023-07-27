/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_expand_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 06:19:51 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 06:19:58 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_size_var(char *str, int *i, int *size, t_list **my_env);

int	size_expanded_redir(char *str, t_list **my_env)
{
	int		i;
	char	quote;
	int		size;

	i = 0;
	quote = 0;
	size = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			set_quote(&quote, str[i], &i);
		else if (quote == str[i])
			set_quote(&quote, 0, &i);
		else if (str[i] == '$' && is_env_var(&str[i], quote))
			get_size_var(str, &i, &size, my_env);
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

static void	get_size_var(char *str, int *i, int *size, t_list **my_env)
{
	char	*getenv;

	if (str[*i + 1] == '?')
	{
		*size += ft_strlen(ft_itoa(g_errno));
		*i += 2;
	}
	else
	{
		getenv = ft_getenv(my_env, get_name_var(str, i), 1);
		*size += ft_strlen(getenv);
		free(getenv);
	}
}
