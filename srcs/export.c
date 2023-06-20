/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:18:09 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/20 19:40:27 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_equal(char *str);
int		is_addition(char *str);
int		ft_equal_size(char *str);
char	*ft_str_skip_add(char *str);
void	ft_print_export(t_list **my_env);
char	**dup_env_sort(char **array, t_list **my_env);

void	ft_export(t_list **my_env, char *str)
{
	t_list	*tmp;

	tmp = *my_env;
	if (!str)
		return (ft_print_export(my_env));
	if (is_alnum(str))
		return (ft_error());
	if (is_addition(str) == 1)
	{
		while (tmp != NULL)
		{
			if (ft_strncmp(tmp->content, str, ft_equal_size(str) - 1) == 0)
			{
				tmp->content = ft_strjoin2(tmp->content, skip_equal(str));
				break ;
			}
			tmp = tmp->next;
		}
	}
	if (is_addition(str) == 1)
		ft_lstadd_back(my_env, ft_lstnew(ft_str_skip_add(str), -1));
	else
		ft_lstadd_back(my_env, ft_lstnew(ft_strdup(str), -1));
}

void	ft_dup_env(char **env, t_list **my_env)
{
	int	runner;

	runner = 0;
	//if (!env)
	// creer un env
	while (env[runner])
	{
		ft_lstadd_back(my_env, ft_lstnew(ft_strdup(env[runner]), -1));
		runner++;
	}
}

char	*ft_getenv(t_list **my_env, char *get_me)
{
	t_list	*runner;
	int		size;

	size = 0;
	runner = *my_env;
	while (runner != NULL)
	{
		size = ft_equal_size(runner->content);
		if (ft_strncmp(runner->content, get_me, size) == 0)
			return (skip_equal(runner->content));
		runner = runner->next;
	}
	return (NULL);
}

int	ft_equal_size(char *str)
{
	int	runner;

	runner = 0;
	while (str[runner] && str[runner] != '=')
		runner++;
	return (runner);
}

char	*skip_equal(char *str)
{
	int	runner;

	runner = ft_equal_size(str);
	if (ft_strlen(str) - runner < 1)
		return (" ");
	return (ft_substr(str, runner + 1, (ft_strlen(str) - runner)));
}

int	is_addition(char *str)
{
	int	runner;

	runner = 0;
	while (str[runner] && str[runner] != '=')
		runner++;
	if (str[runner] - 1 && str[runner - 1] == '+')
		return (1);
	return (0);
}

char	*ft_str_skip_add(char *str)
{
	int		runner;
	int		index;
	int		count;
	char	*output;

	index = 0;
	runner = 0;
	count = ft_strlen(str);
	output = malloc(sizeof(char) * count);
	while (runner < count)
	{
		if (str[runner] == '+')
			runner++;
		output[index] = str[runner];
		runner++;
		index++;
	}
	output[index] = '\0';
	return (output);
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
