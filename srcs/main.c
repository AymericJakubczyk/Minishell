/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:11:04 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/13 14:12:15 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(char *s1, char*s2);
static int	ft_exit(char *array);

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	char	*prompt;
	char	*eenv;

	(void) ac;
	(void) av;
	prompt = NULL;
	cmd = ft_strdup("");
	while (ft_exit(cmd) == 0)
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

static int	ft_exit(char *array)
{
	int		runner;
	int		count;
	char	*string;

	count = 0;
	runner = 0;
	if (ft_strlen(array) < 3)
		return (0);
	string = malloc(sizeof(char) * (no_whitespaces(array)) + 1);
	if (!string)
		return (-1);
	while (array[runner++])
	{
		if (array[runner] != ' ' && array[runner] != '\t')
		{
			string[count] = array[runner];
			count++;
		}
	}
	string[count] = '\0';
	if (ft_strcmp(string, "exit") == 0)
		return (free(string), -1);
	if ((ft_strncmp(string, "exit", 4) == 0) && (ft_strcmp(string, "exit") != 0))
		return (free(string), ft_error(ERROR_21, "exit"), -1);
	return (0);
}

int	no_whitespaces(char	*array)
{
	int	runner;
	int	count;

	count = 0;
	runner = 0;
	while (array[runner])
	{
		if (array[runner] != ' ' && array[runner] != '\t')
			count++;
		runner++;
	}
	return (count);
}
