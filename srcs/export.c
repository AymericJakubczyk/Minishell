/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:18:09 by cprojean          #+#    #+#             */
/*   Updated: 2023/06/14 09:42:35 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_export(t_list *list, char **env)
{
	
	return (0);
}

char	**ft_arr_dup_add(char **env, char *string)
{
	char	**dup;
	int		runner;

	runner = 0;
	while(env[runner])
	{
		ft_strdup(env[runner]);
		runner++;
	}
	if (ft_is_quote(string) == 1)
		dup[runner] = malloc(sizeof(string) - 1);
	else
		dup[runner] = malloc(sizeof(string) + 1);
	add_str(dup[runner], string);
}

int	ft_tablen(char **tab)
{
	int	runner;

	runner = 0;
	while (tab[runner])
		runner++;
	return (runner);
}

int	ft_is_quote(char *str)
{
	int	runner;

	runner = 0;
	while (str[runner])
	{
		if (str[runner] == '\"')
			return (1);
		runner++;
	}
	return (0);
}

void	add_str(char *str, char *copy)
{
	int	runner;
	int	tmp;

	tmp = 0;
	runner = 0;
	while (copy[tmp])
	{
		if (copy[tmp] != '\"')
		{
			*str[runner] = copy[tmp];
			runner++;
		}
		tmp++;
	}
}
