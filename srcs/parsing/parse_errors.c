/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:27:05 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/25 20:53:41 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirect_out(t_parse *input, int runner);
static int	check_redirect_in(t_parse *input, int runner);
static int	check_pipe(t_parse *input, int runner);
static int	good_type(int type);

int	check_parse(t_parse *input)
{
	int	runner;

	runner = 0;
	while (input[runner].str)
	{
		if (input[runner].str[0] == '|')
			if (check_pipe(input, runner) == -1)
				return (-1);
		if (input[runner].str[0] == '<')
			if (check_redirect_in(input, runner) == -1)
				return (-1);
		if (input[runner].str[0] == '>')
			if (check_redirect_out(input, runner) == -1)
				return (-1);
		runner++;
	}
	return (next_parse_check(input));
}

static int	check_pipe(t_parse *input, int runner)
{
	if (input[runner + 1].str && input[runner + 1].str[0] == '|')
	{
		if (input[runner + 2].str && input[runner + 2].str[0] == '|')
			return (ft_error(ERROR_6, NULL), -1);
		else
			return (ft_error(ERROR_7, NULL), -1);
	}
	if (runner - 1 >= 0 && !good_type(input[runner - 1].type))
		return (ft_error(ERROR_7, NULL), -1);
	return (0);
}

static int	check_redirect_in(t_parse *input, int runner)
{
	if (input[runner + 1].str && input[runner + 1].str[0] == '<')
	{
		if (input[runner + 1].str[1] && input[runner + 1].str[1] == '<')
			return (ft_error(ERROR_4, NULL), -1);
		else
			return (ft_error(ERROR_5, NULL), -1);
	}
	return (0);
}

static int	check_redirect_out(t_parse *input, int runner)
{
	if (input[runner + 1].str && input[runner + 1].str[0] == '>')
	{
		if (input[runner + 1].str[1] && input[runner + 1].str[1] == '>')
			return (ft_error(ERROR_2, NULL), -1);
		else
			return (ft_error(ERROR_3, NULL), -1);
	}
	return (0);
}

static int	good_type(int type)
{
	if (type == REDIRECT_IN || type == REDIRECT_OUT || type == APPEND || type == HEREDOC)
		return (0);
	return (1);
}