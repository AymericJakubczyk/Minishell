/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:11:04 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/25 18:07:40 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_strcmp(char *s1, char*s2);
void		handler(int sig);
void minishell(t_list **my_env);

int	main(int ac, char **av, char **env)
{
	t_list	*my_env;
	(void) ac;
	(void) av;
	if (!env || !env[0])
		ft_create_env(&my_env);
	else
		ft_dup_env(env, &my_env);
	minishell(&my_env);
	rl_clear_history();
	exit (1);
}

void minishell(t_list **my_env)
{
	char	*cmd;
	char	*prompt;

	prompt = NULL;
	cmd = ft_strdup("");
	while (ft_exit(cmd) == 0)
	{
		free(cmd);
		ft_free(prompt, NULL);
		prompt = ft_get_prompt(my_env);
		if (!prompt)
			exit(0);
		signal(SIGINT, handler);
		cmd = readline(prompt);
		if (!cmd)
			break;
		if (ft_strlen(cmd) != 0)
			add_history(cmd);
		parse_and_exec(cmd, my_env);
	}
	if (!cmd)
		ft_printf("\nCTRL-D\n");
	ft_free(prompt, NULL);
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
