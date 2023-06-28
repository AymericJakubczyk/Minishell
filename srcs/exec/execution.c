/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:38:49 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/27 19:38:25 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		how_many_cmds(t_parse *parse);
void	ex_child(t_parse *parse, t_list **env, int runner);

void print_all(char **all_limiter, char **str_heredoc)
{
	int i;

	i = 0;
	while (all_limiter[i])
	{
		ft_printf("limiter %d : %s \nSTRING : \n%sFIN STR\n", i, all_limiter[i], str_heredoc[i]);
		i++;
	}
}

void	execution(t_parse *parse, t_list **my_env)
{
	int	pipes;
	t_exec	my_struct;

	if (heredoc_in(parse))
	{
		do_heredoc(parse, &my_struct, my_env);
		//print_all(my_struct.all_limiter, my_struct.str_heredoc);
	}
	//Heredoc here
	pipes = how_many_cmds(parse);
	if (pipes != 0)
	{
		ft_printf("Pipes\n");
		// exec_with_forks(parse, my_env);
	}
	else
		single_cmd(parse, my_env);
}

int	how_many_cmds(t_parse *parse)
{
	int	runner;
	int	count;

	count = 0;
	runner = 0;
	while (parse[runner].str)
	{
		if (parse[runner].type == PIPEE)
			count++;
		runner++;
	}
	return (count);
}

void	ex_child(t_parse *parse, t_list **env, int runner)
{
	char	**arg;
	char	*path;
	int		index;
	int		count;

	count = 0;
	index = 1;
	path = get_path(parse[runner].str, env);
	if (!path)
		exit (1);
	count = how_much_args(parse, runner);
	arg = malloc(sizeof(char *) * count + 1);
	arg[0] = ft_strdup(parse[runner++].str);
	while (parse[runner].str && parse[runner].type == CMD_ARG)
	{
		arg[index] = ft_strdup(parse[runner].str);
		runner++;
		index++;
	}
	if (execve(path, arg, NULL) == -1)
		ft_printf("Execution error \n");
}

int	how_much_args(t_parse *parse, int runner)
{
	int	index;

	index = 0;
	while (parse[runner].str && parse[runner].type)
	{
		index++;
		runner++;
	}
	return (index);
}
