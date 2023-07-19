/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:11:04 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/19 10:22:49 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_errno;

void	handler(int sig);
void	init_data(t_exec *data, char **env);
void	minishell(t_list **my_env, char **env, t_exec *data);
void	dup_entrys(t_exec *data);

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
	minishell(&my_env, env, &data);
	ft_lstclear(&my_env, free);
	rl_clear_history();
	exit (1);
}

void	minishell(t_list **my_env, char **env, t_exec *data)
{
	char	*cmd;
	char	*prompt;

	cmd = ft_strdup("");
	while (42)
	{
		init_data(data, env);
		free(cmd);
		prompt = ft_get_prompt(my_env);
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		cmd = readline(prompt);
		ft_free(prompt, NULL);
		if (!cmd)
			break ;
		if (ft_strlen(cmd) != 0)
			add_history(cmd);
		parse_and_exec(cmd, my_env, data);
		dup_entrys(data);
		double_close(&data->fd_in, &data->fd_out);
	}
	if (!cmd)
		ft_printf("\nCTRL-D\n");
	free(cmd);
}
//ignorer le ctrl-'\'

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
	data->current_fd_in = data->fd_in;
	data->fd_out = dup(1);
	data->current_fd_out = data->fd_out;
	data->mode = 0;
	data->env = env;
}

void	dup_entrys(t_exec *data)
{
	if (data->current_fd_in != data->fd_in)
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			ft_printf("Dup2 failed to restore ALED %d\n", data->fd_in);
	if (data->current_fd_out != data->fd_out)
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			ft_printf("Dup2 failed to restore PUTAIN %d\n", data->fd_out);
}
