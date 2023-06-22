/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:11:04 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/22 11:36:33 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char*s2);
static int	ft_exit(char *array);
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
	t_list	*my_env;

	prompt = NULL;
	cmd = ft_strdup("");
	while (ft_exit(cmd) == 0)
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
int	ft_strcmp(char *s1, char*s2)
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
	runner = -1;
	if (ft_strcmp(array, "exit") == 0)
		return (-1);
	string = malloc(sizeof(char) * (no_whitespaces(array)) + 1);
	if (!string)
		return (-12);
	while (array[++runner])
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
	return (free(string), 0);
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

void	handler(int sig)
{
	char *prompt;
	
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
