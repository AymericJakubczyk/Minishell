/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:03:50 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/27 15:33:30 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_export_type(t_list **my_env, t_parse *parse, \
		int runner, t_list *tmp)
{
	if (is_allready_export(my_env, parse[runner].str) && \
	parse[runner].str[0] != '=')
		export_again(my_env, parse[runner].str);
	else if (is_addition(parse[runner].str) == 1)
		add_to_existing_one(tmp, parse[runner].str);
	else
		next_check_export_type(my_env, parse, runner);
}

void	next_check_export_type(t_list **my_env, t_parse *parse, \
		int runner)
{
	char	*export;

	if (ft_equal_size(parse[runner].str) == 0 && \
	is_alpha_export(parse[runner].str) != 0 && \
	(parse[runner].str[0]) != '=')
	{
		export = ft_strdup(parse[runner].str);
		if (!export)
			return (ft_error(ERROR_42, NULL, 1));
		ft_lstadd_back(my_env, ft_lstnew(export, -1));
	}
	else if (is_alpha_export(parse[runner].str) == 0)
		ft_error(ERROR_22, parse[runner].str, 1);
	else if (parse[runner].str[0] == '=')
		ft_error(ERROR_22, parse[runner].str, 1);
	else
	{
		export = ft_str_skip_add(parse[runner].str);
		if (!export)
			return (ft_error(ERROR_42, NULL, 1));
		ft_lstadd_back(my_env, ft_lstnew(export, -1));
		free(export);
	}
}

int	ft_equal_ind(char *str)
{
	size_t	runner;

	runner = 0;
	if (!str)
		return (0);
	while (str[runner] && str[runner] != '=')
		runner++;
	if (str[runner] == '=')
		return (runner);
	else
		return (0);
}

void	print_it(char **array, t_list **my_env)
{
	char	*printable;
	int		i;

	i = 0;
	while (i < ft_lstsize(*my_env))
	{
		printable = add_quotes(array[i]);
		if (!printable)
			return ;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(printable, 1);
		ft_putchar_fd('\n', 1);
		free(printable);
		i++;
	}
}

int	is_two_dash(char *str)
{
	if (ft_strlen(str) == 2)
		if (str[0] == '-')
			if (str[1] == '-')
				return (1);
	return (0);
}
