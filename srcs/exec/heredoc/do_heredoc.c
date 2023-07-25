/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:20:03 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/25 04:55:55 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nbr_limiter(t_parse *parse);
static void	fill_all_limiter(t_parse *parse, t_exec *my_struct);
static void	get_heredoc(t_exec *my_struct, t_list **my_env);

int	do_heredoc(t_parse *parse, t_exec *data, t_list **my_env)
{
	data->nbr_limiter = get_nbr_limiter(parse);
	data->all_limiter = malloc(sizeof(char *) * (data->nbr_limiter + 1));
	if (!data->all_limiter)
		return (-1);
	data->str_heredoc = malloc(sizeof(char *) * (data->nbr_limiter + 1));
	if (!data->str_heredoc)
		return (free(data->all_limiter), -1);
	fill_all_limiter(parse, data);
	get_heredoc(data, my_env);
	return (1);
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
	int		stdin_copy;

	stdin_copy = dup(0);
	i = 0;
	//ft_printf("test\n");
	limiter = limiter_without_quote(my_struct->all_limiter[i]);
	quote_in_lim = quote_in(my_struct->all_limiter[i]);
	g_errno = 0;
	while (i < my_struct->nbr_limiter)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, signal_heredoc);
		str = readline(">");
		if (!str)
		{
			i++;
			if (g_errno == 130)
			{
				ft_printf("\n");
				my_struct->str_heredoc[my_struct->nbr_limiter] = NULL;
				dup2(stdin_copy, 0);
				close(stdin_copy);
				free(limiter);
				//free tout
				break ;
			}
			else
				ft_printf("minihell: warning: here-document delimited by end-of-file (wanted '%s')\n" ,limiter);
			free(limiter);
			if (i < my_struct->nbr_limiter)
			{
				limiter = limiter_without_quote(my_struct->all_limiter[i]);
				quote_in_lim = quote_in(my_struct->all_limiter[i]);
			}
		}
		else if (ft_strcmp(str, limiter) == 0)
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
