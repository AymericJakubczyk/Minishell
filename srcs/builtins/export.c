/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:18:09 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/28 11:25:09 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(t_list **my_env);
char	**dup_env_sort(char **array, t_list **my_env);
void	export_again(t_list **my_env, char *str);
void	add_to_existing_one(t_list *tmp, char *str);

void	ft_export(t_list **my_env, char *str)
{
	t_list	*tmp;

	tmp = *my_env;
	if (!str)
		return (ft_print_export(my_env));
	if (is_allready_export(my_env, str))
		return (export_again(my_env, str));
	if (is_addition(str) == 1)
		add_to_existing_one(tmp, str);
	if (is_addition(str) == 1)
		ft_lstadd_back(my_env, ft_lstnew(ft_str_skip_add(str), -1));
	else
		ft_lstadd_back(my_env, ft_lstnew(ft_strdup(str), -1));
}

void	add_to_existing_one(t_list *tmp, char *str)
{
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, str, ft_equal_size(str) - 1) == 0)
		{
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
		ft_putstr_fd(array[i], 1);
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
