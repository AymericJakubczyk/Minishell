/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:11:04 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/11 18:41:49 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(char *s1, char*s2);

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	char	*prompt;

	(void) ac;
	(void) av;
	(void) env;
	prompt = NULL;
	cmd = ft_strdup("");
	while (ft_strcmp(cmd, "exit") != 0)
	{
		free(cmd);
		ft_free(prompt, NULL);
		prompt = ft_get_prompt();
		cmd = readline(prompt);
		add_history(cmd);
		parse_and_exec(cmd);
	}
	ft_free(prompt, NULL);
	rl_clear_history();
	free(cmd);
	exit (1);
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
