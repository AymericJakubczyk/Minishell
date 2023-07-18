/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_parse_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:38:13 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/18 15:29:43 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirect_args(t_parse *input, int runner);
static int	check_pipe_args(t_parse *input, int runner);

int	next_parse_check(t_parse *input)
{
	int	runner;

	runner = 0;
	while (input[runner].str)
	{
		if (input[runner].type == REDIRECT_IN || input[runner].type == HEREDOC)
			if (check_redirect_args(input, runner) == -1)
				return (-1);
		if (input[runner].type == REDIRECT_OUT || input[runner].type == APPEND)
			if (check_redirect_args(input, runner) == -1)
				return (-1);
		if (input[runner].type == PIPEE)
			if (check_pipe_args(input, runner) == -1)
				return (-1);
		runner++;
	}
	return (0);
}

static int	check_redirect_args(t_parse *input, int runner)
{
	if (input[runner + 1].str && input[runner + 1].str[0])
		return (0);
	else
		return (ft_error(ERROR_19, NULL, 2), -1);
}

static int	check_pipe_args(t_parse *input, int runner)
{
	if (((runner - 1) >= 0) && input[runner + 1].str && \
		input[runner + 1].str[0])
		return (0);
	else
		return (ft_error(ERROR_20, NULL, 2), -1);
}
