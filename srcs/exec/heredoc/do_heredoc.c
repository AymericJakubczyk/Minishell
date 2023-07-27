/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:20:03 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/27 02:43:25 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nbr_limiter(t_parse *parse);
static void	fill_all_limiter(t_parse *parse, t_exec *my_struct);

int	do_heredoc(t_parse *parse, t_exec *data, t_list **my_env)
{
	data->nbr_limiter = get_nbr_limiter(parse);
	data->all_limiter = malloc(sizeof(char *) * (data->nbr_limiter + 1));
	if (!data->all_limiter)
		return (ft_error(ERROR_42, NULL, 1), -1);
	data->str_heredoc = malloc(sizeof(char *) * (data->nbr_limiter + 1));
	if (!data->str_heredoc)
		return (ft_error(ERROR_42, NULL, 1), free(data->all_limiter), -1);
	fill_all_limiter(parse, data);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_heredoc);
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
