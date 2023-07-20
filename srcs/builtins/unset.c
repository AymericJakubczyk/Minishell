/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:51:36 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/21 01:18:16 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_alnum(char *str);
void	first_var_unset(t_list **my_env);
void	unset_cmd(t_list **my_env, t_parse *parse, int index, int *count);

void	ft_unset(t_list **my_env, t_parse *parse)
{
	int		count;
	int		index;

	index = 1;
	count = 0;
	g_errno = 0;
	while (parse[index].str)
	{
		if (parse[index].type == CMD_ARG)
		{
			unset_cmd(my_env, parse, index, &count);
		}
		index++;
	}
}

void	unset_cmd(t_list **my_env, t_parse *parse, int index, int *count)
{
	t_list	*runner;
	t_list	*tmp;

	if (is_alpha(parse[index].str) == 0)
		return (ft_error(ERROR_22, parse[index].str, 1));
	runner = *my_env;
	tmp = *my_env;
	while (runner != NULL)
	{
		if (ft_strncmp(runner->content, parse[index].str, \
		ft_strlen(parse[index].str)) == 0 && count != 0)
		{
			free(runner->content);
			free(runner);
			tmp->next = runner->next;
		}
		else if (ft_strncmp(runner->content, parse[index].str, \
		ft_strlen(parse[index].str)) == 0 && count == 0)
			first_var_unset(my_env);
		tmp = runner;
		runner = runner->next;
	}
}

void	first_var_unset(t_list **my_env)
{
	t_list	*tmp;
	t_list	*scnd;

	tmp = *my_env;
	scnd = *my_env;
	scnd = scnd->next;
	tmp->next = scnd->next;
	tmp->content = ft_strdup(scnd->content);
	free(scnd->content);
	free(scnd);
}

int	is_alpha(char *str)
{
	int	runner;

	runner = 0;
	while (str[runner] && str[runner] != '=')
	{
		if (ft_isalpha(str[runner]) == 0 && str[runner] != '_')
			return (0);
		runner++;
	}
	return (1);
}

int	is_alpha_export(char *str)
{
	int	runner;

	runner = 0;
	if (str[runner] != '=' && ft_isalpha(str[runner]) == 0)
		return (0);
	while (str[runner] && str[runner] != '=')
	{
		if (ft_isalnum(str[runner]) == 0 && str[runner] != '_' )
		{
			if (str[runner] == '+' && str[runner + 1] && str[runner + 1] == '=')
				return (1);
			else
				return (0);
		}
		runner++;
	}
	return (1);
}
