/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:10:46 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/26 06:39:07 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_env_var(char *str, char quote);
void	fill_expanded_redir(t_entry *entry, char *str, t_list **my_env);
char	*get_name_var(char *str, int *i);
void	add_var(t_entry *entry, char *str, int *j, char quote);
void	set_context(t_entry *entry, int j, char quote);
int		size_expanded_redir(char *str, t_list **my_env);
char	*colapse_entry(t_entry *entry);
int		check_expanded_redir(t_entry *entry);

int	check_all_redirect(t_parse *parse, t_list **my_env, t_exec *data)
{
	int	i;

	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == REDIRECT_IN && \
		!check_redirect(parse[i + 1], my_env, IN))
		{
			ft_lstclear(my_env, free);
			free_all_parse(data->parse);
			rl_clear_history();
			return (0);
		}
		else if ((parse[i].type == REDIRECT_OUT || parse[i].type == APPEND) \
		&& !check_redirect(parse[i + 1], my_env, OUT))
		{
			ft_lstclear(my_env, free);
			free_all_parse(data->parse);
			rl_clear_history();
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_redirect(t_parse parse, t_list **my_env, int mode)
{
	char	*expanded;

	expanded = expand_redirect(parse, my_env);
	if (!expanded)
		return (0);
	if (mode == IN && access(expanded, F_OK | R_OK) == -1)
	{
		ft_dprintf("(s)Hell : %s: %s\n", expanded, strerror(errno));
		return (free(expanded), 0);
	}
	if (mode == OUT && open(expanded, O_WRONLY | O_CREAT, 0644) == -1)
	{
		ft_dprintf("(s)Hell : %s: %s\n", expanded, strerror(errno));
		return (free(expanded), 0);
	}
	return (free(expanded), 1);
}

char	*expand_redirect(t_parse parse, t_list **my_env)
{
	t_entry	*entry;
	char	*expanded;

	expanded = NULL;
	entry = malloc(sizeof(t_entry) * \
	(size_expanded_redir(parse.str, my_env) + 1));
	if (!entry)
	{
		return (ft_error(ERROR_42, NULL, 1), NULL);
	}
	fill_expanded_redir(entry, parse.str, my_env);
	if (!check_expanded_redir(entry))
		return (NULL);
	expanded = colapse_entry(entry);
	free(entry);
	return (expanded);
}

int	size_expanded_redir(char *str, t_list **my_env)
{
	int		i;
	char	quote;
	char	*getenv;
	int		size;

	i = 0;
	quote = 0;
	size = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			i++;
		}
		else if (quote == str[i])
		{
			quote = 0;
			i++;
		}
		else if (str[i] == '$' && is_env_var(&str[i], quote))
		{
			if (str[i + 1] == '?')
			{
				size += ft_strlen(ft_itoa(g_errno));
				i += 2;
			}
			else
			{
				getenv = ft_getenv(my_env, get_name_var(str, &i), 1);
				size += ft_strlen(getenv);
				free(getenv);
			}
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

int	is_env_var(char *str, char quote)
{
	if (quote != '\'' && str[1] && \
		(ft_isalnum(str[1]) || str[1] == '_' || str[1] == '?'))
		return (1);
	return (0);
}

char	*get_name_var(char *str, int *i)
{
	char	*name;

	name = ft_strdup("");
	*i += 1;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		name = ft_strjoin2(name, char_to_str(str[*i]));
		*i += 1;
	}
	return (name);
}

void	fill_expanded_redir(t_entry *entry, char *str, t_list **my_env)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			i++;
		}
		else if (quote == str[i])
		{
			quote = 0;
			i++;
		}
		else if (str[i] == '$' && is_env_var(&str[i], quote))
		{
			if (str[i + 1] == '?')
			{
				add_var(entry, ft_itoa(g_errno), &j, quote);
				i += 2;
			}
			else
				add_var(entry, ft_getenv(my_env, get_name_var(str, &i), 1), \
				&j, quote);
		}
		else
		{
			entry[j].c = str[i];
			entry[j].type = -1;
			set_context(entry, j, quote);
			i++;
			j++;
		}
	}
	entry[j].c = 0;
}

void	add_var(t_entry *entry, char *str, int *j, char quote)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		entry[*j].c = str[i];
		entry[*j].type = -1;
		set_context(entry, *j, quote);
		*j += 1;
		i++;
	}
	free(str);
}

void	set_context(t_entry *entry, int j, char quote)
{
	if (quote == 0)
		entry[j].context = NO_QUOTE;
	else if (quote == '\'')
		entry[j].context = SI_QUOTE;
	else
		entry[j].context = DO_QUOTE;
}

int	check_expanded_redir(t_entry *entry)
{
	int	i;
	int	last_ind_char;

	i = 0;
	last_ind_char = get_ind_last_char(entry);
	while (entry[i].c && (entry[i].c == ' ' || \
	entry[i].c == '\t') && entry[i].context == NO_QUOTE)
		i++;
	if (!entry[i].c)
		return (ft_dprintf("AMBIGUOUS REDIRECTION !\n"), 0);
	while (entry[i].c && i <= last_ind_char)
	{
		if ((entry[i].c == ' ' || entry[i].c == '\t') \
		&& entry[i].context == NO_QUOTE)
			return (ft_dprintf("AMBIGUOUS REDIRECTION !\n"), 0);
		i++;
	}
	return (1);
}

int	get_ind_last_char(t_entry *entry)
{
	int	i;

	i = 0;
	while (entry[i].c)
		i++;
	i--;
	while (i >= 0 && (entry[i].c == ' ' || entry[i].c == '\t') \
	&& entry[i].context == NO_QUOTE)
		i--;
	return (i);
}

char	*colapse_entry(t_entry *entry)
{
	int		i;
	char	*expanded;
	int		last_ind_char;

	i = 0;
	last_ind_char = get_ind_last_char(entry);
	expanded = ft_strdup("");
	while (entry[i].c && (entry[i].c == ' ' || entry[i].c == '\t') \
	&& entry[i].context == NO_QUOTE)
		i++;
	while (entry[i].c && i <= last_ind_char)
	{
		expanded = ft_strjoin2(expanded, char_to_str(entry[i].c));
		i++;
	}
	return (expanded);
}

int	check_all_redirect_without_fork(t_parse *parse, t_list **my_env)
{
	int	i;

	i = 0;
	while (parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == REDIRECT_IN && \
		!check_redirect(parse[i + 1], my_env, IN))
		{
			return (0);
		}
		else if ((parse[i].type == REDIRECT_OUT || parse[i].type == APPEND) \
		&& !check_redirect(parse[i + 1], my_env, OUT))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
