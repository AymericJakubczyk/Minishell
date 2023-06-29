/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:11:04 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/29 17:53:51 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_errno;

void	handler(int sig);
void	init_data(t_exec *data, char **env);
void	minishell(t_list **my_env, char **env, t_exec *data);

int	main(int ac, char **av, char **env)
{
	t_list	*my_env;
	t_exec	data;

	(void) ac;
	(void) av;
	g_errno = 0;
	my_env = NULL;
	if (!env || !env[0])
		ft_create_env(&my_env);
	else
		ft_dup_env(env, &my_env);
	init_data(&data, env);
	minishell(&my_env, env, &data);
	ft_lstclear(&my_env, free);
	double_close(data.fd_in, data.fd_out);
	rl_clear_history();
	exit (1);
}

void	minishell(t_list **my_env, char **env, t_exec *data)
{
	char	*cmd;
	char	*prompt;

	cmd = ft_strdup("");
	while (ft_exit(cmd) == 0)
	{
		free(cmd);
		prompt = ft_get_prompt(my_env);
		signal(SIGINT, handler);
		cmd = readline(prompt);
		ft_free(prompt, NULL);
		if (!cmd)
			break ;
		if (ft_strlen(cmd) != 0)
			add_history(cmd);
		parse_and_exec(cmd, my_env, data);
	}
	if (!cmd)
		ft_printf("\nCTRL-D\n");
	free(cmd);
}

void	handler(int sig)
{
	(void) sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_data(t_exec *data, char **env)
{
	data->fd_in = dup(0);
	data->fd_out = dup(1);
	data->mode = 0;
	data->env = env;
}
