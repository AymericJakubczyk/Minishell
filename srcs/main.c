/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:11:04 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/21 14:56:44 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(char *s1, char*s2);
void		handler(int sig);
void		minishell(char **env);

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	minishell(env);
	rl_clear_history();
	exit (1);
}

void minishell(char **env)
{
	char	*cmd;
	char	*prompt;

	prompt = NULL;
	cmd = ft_strdup("");
	while (cmd && ft_strcmp(cmd, "exit") != 0)
	{
		free(cmd);
		ft_free(prompt, NULL);
		prompt = ft_get_prompt();
		if (!prompt)
			exit(0);
		signal(SIGINT, handler);
		cmd = readline(prompt);
		if (!cmd)
			break;
		if (ft_strlen(cmd) != 0)
			add_history(cmd);
		parse_and_exec(cmd);
	}
	if (!cmd)
		ft_printf("\nCTRL-D\n");
	ft_free(prompt, NULL);
	free(cmd);
}

//A refaire car inutile pour le exit car cmd "exit " n'est pas pris en compte
static int	ft_strcmp(char *s1, char*s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '\n' && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	if (s1[i] == '\n')
		return (s2[i]);
	return (s1[i] - s2[i]);
}

void	handler(int sig)
{
	char *prompt;
	
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}