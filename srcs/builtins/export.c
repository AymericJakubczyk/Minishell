/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:18:09 by cprojean          #+#    #+#             */
/*   Updated: 2023/07/18 14:41:59 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(t_list **my_env);
char	**dup_env_sort(char **array, t_list **my_env);
void	export_again(t_list **my_env, char *str);
void	add_to_existing_one(t_list *tmp, char *str);

void	ft_export(t_list **my_env, t_parse *parse)
{
	t_list	*tmp;
	int		runner;

	tmp = *my_env;
	g_errno = 0;
	runner = 1;
	if (!parse[runner].str || parse[runner].type != CMD_ARG)
		return (ft_print_export(my_env));
	while (parse[runner].str)
	{
		if (parse[runner].type == CMD_ARG)
			check_export_type(my_env, parse, runner, tmp);
		runner++;
	}
}

void	add_to_existing_one(t_list *tmp, char *str)
{
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, str, ft_equal_size(str) - 1) == 0)
		{
			if (equal(tmp->content) == 0)
				tmp->content = ft_strjoin3(tmp->content, "=");
			tmp->content = ft_strjoin2(tmp->content, skip_equal(str));
			if (!tmp->content)
				return ;
			break ;
		}
		tmp = tmp->next;
	}
}

void	export_again(t_list **my_env, char *str)
{
	t_list	*runner;

	runner = *my_env;
	while (runner != NULL)
	{
		if (ft_strncmp(runner->content, str, ft_equal_size(str)) == 0)
		{
			free(runner->content);
			runner->content = ft_strdup(str);
			return ;
		}
		runner = runner->next;
	}
}

void	ft_print_export(t_list **my_env)
{
	char	**array;
	t_list	*export;
	int		i;

	export = *my_env;
	i = 0;
	array = malloc(sizeof(char *) * ft_lstsize(export));
	if (!array)
		return ;
	while (export != NULL)
	{
		array[i++] = export->content;
		export = export->next;
	}
	i = 0;
	array = dup_env_sort(array, my_env);
	while (i < ft_lstsize(*my_env))
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(add_quotes(array[i]), 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	free(array);
}

char	**dup_env_sort(char **array, t_list **my_env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (i < ft_lstsize(*my_env))
	{
		j = i + 1;
		while (j < ft_lstsize(*my_env))
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				str = array[i];
				array[i] = array[j];
				array[j] = str;
			}
			j++;
		}
		i++;
	}
	return (array);
}
