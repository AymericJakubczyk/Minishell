/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:14:56 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/30 09:14:57 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	exec_cmd(t_parse *parse, int num_cmd, t_list **my_env, t_exec *data);
int	get_start_cmd(t_parse *parse, int num_cmd);
void	do_redirect_in(t_parse *parse, t_list **my_env, t_exec *data);

void	exec_with_forks(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	nbr_cmd;
	int num_cmd;

	nbr_cmd = how_many_cmds(parse) + 1;
	num_cmd = 0;
	while (num_cmd < nbr_cmd)
	{
		//fork();
			exec_cmd(parse, num_cmd, my_env, data);
		num_cmd++;
	}
}

void	exec_cmd(t_parse *parse, int num_cmd, t_list **my_env, t_exec *data)
{
	char **arg;
	char *path;
	int start_cmd;

	start_cmd = get_start_cmd(parse, num_cmd);
	if (redirect_in(&parse[start_cmd]))
		do_redirect_in(&parse[start_cmd], my_env, data);
	// // else 
	// // 	do_classique_pipe();
	// if (redirect_out(parse, num_cmd));
	// 	do_redirect_out(parse, num_cmd, my_env, data);
	// // else
	// // 	do_classique_out_pipe();
	// arg = get_arg(parse, num_cmd);
	// // if (!arg)
	// // 	exit
	// // if (is_builtin(arg[0]))
	// // 	do_builtin();
	// path = get_path(arg[0], my_env);
	// // if (!path)
	// // 	exit
	// execve(path, arg, data->env);
	// // exit car execve a crash si ici
}

int	get_start_cmd(t_parse *parse, int num_cmd)
{
	int start;
	int n_cmd;

	start = 0;
	n_cmd = 0;
	while (n_cmd < num_cmd && parse[start].str)
	{
		if (parse[start].type == PIPEE)
			n_cmd++;
		start++;
	}
	return (start);
}

int	redirect_in(t_parse *parse)
{
	int i;

	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == HEREDOC || parse[i].type == REDIRECT_IN)
			return (1);
		i++;
	}
	return (0);
}

void	do_redirect_in(t_parse *parse, t_list **my_env, t_exec *data)
{
	if (check_all_redirect_in(parse, my_env) == 0) 
	{
		ft_printf("NOT GOOD REDIRECT\n");
		//exit(1); //faudra free et exit proprement avec le bon message d'erreur
	}
	else
	{
		ft_printf("GOOD REDIRECT\n");
	}
}

int	check_all_redirect_in(t_parse *parse, t_list **my_env)
{
	int i;

	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == REDIRECT_IN && !check_redirect(parse[i + 1], my_env))
			return (0);
		i++;
	}
	return (1);
}


