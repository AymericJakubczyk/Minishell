/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:20:03 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/19 10:03:13 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nbr_limiter(t_parse *parse);
static void	fill_all_limiter(t_parse *parse, t_exec *my_struct);
static void	get_heredoc(t_exec *my_struct, t_list **my_env);

void	do_heredoc(t_parse *parse, t_exec *my_struct, t_list **my_env)
{
	my_struct->nbr_limiter = get_nbr_limiter(parse);
	my_struct->all_limiter = malloc(sizeof(char *) * \
		(my_struct->nbr_limiter + 1));
	my_struct->str_heredoc = malloc(sizeof(char *) * \
		(my_struct->nbr_limiter + 1));
	fill_all_limiter(parse, my_struct);
	get_heredoc(my_struct, my_env);
	//ft_printf("string hd : %s\n", ft_get_str_hd(parse, my_struct, 2));
}

static int	get_nbr_limiter(t_parse *parse)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (parse[i].str)
	{
		if (parse[i].type == LIMITER)
			nbr++;
		i++;
	}
	return (nbr);
}

static void	fill_all_limiter(t_parse *parse, t_exec *my_struct)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parse[i].str)
	{
		if (parse[i].type == LIMITER)
		{
			my_struct->all_limiter[j] = parse[i].str;
			my_struct->str_heredoc[j] = ft_strdup("");
			j++;
		}
		i++;
	}
	my_struct->all_limiter[j] = NULL;
}

static void	get_heredoc(t_exec *my_struct, t_list **my_env)
{
	int		i;
	int		quote_in_lim;
	char	*str;
	char	*limiter;

	i = 0;
	ft_printf("test\n");
	limiter = limiter_without_quote(my_struct->all_limiter[i]);
	quote_in_lim = quote_in(my_struct->all_limiter[i]);
	while (i < my_struct->nbr_limiter)
	{
		str = readline(">");
		if (ft_strcmp(str, limiter) == 0)
		{
			free(str);
			free(limiter);
			i++;
			if (i < my_struct->nbr_limiter)
			{
				limiter = limiter_without_quote(my_struct->all_limiter[i]);
				quote_in_lim = quote_in(my_struct->all_limiter[i]);
			}
		}
		else
		{
			if (!quote_in_lim)
				str = expand_heredoc(str, my_env);
			str = ft_strjoin2(str, ft_strdup("\n"));
			my_struct->str_heredoc[i] = ft_strjoin2(my_struct->str_heredoc[i], str);
		}
	}
	my_struct->str_heredoc[i] = NULL;
}
