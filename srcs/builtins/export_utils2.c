/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:03:50 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/18 15:31:20 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_export_type(t_list **my_env, t_parse *parse, int runner, t_list *tmp)
{
	if (is_allready_export(my_env, parse[runner].str))
		export_again(my_env, parse[runner].str);
	else if (is_addition(parse[runner].str) == 1)
		add_to_existing_one(tmp, parse[runner].str);
	else if (ft_equal_size(parse[runner].str) == 0)
		ft_lstadd_back(my_env, ft_lstnew(ft_strdup(parse[runner].str), -1));
	else if (is_alpha_export(parse[runner].str) == 0)
		ft_error(ERROR_22, parse[runner].str, 1);
	else
	{
		ft_lstadd_back(my_env, \
		ft_lstnew(ft_str_skip_add(parse[runner].str), -1));
	}
}
