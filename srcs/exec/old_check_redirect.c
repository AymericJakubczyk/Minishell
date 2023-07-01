
#include "minishell.h"

char *expand_redirect(t_parse parse, t_list **my_env);
void	redir_without_quote(char *str, char **expanded);
void	do_expand(char *str, t_list **my_env, char **expanded);
char *get_name_var(char *str, int *i);

int	check_redirect(t_parse parse, t_list **my_env)
{
	char	*expanded;

	expanded = expand_redirect(parse, my_env);
	ft_printf("infile : %s|\n", expanded);
	if ((env_in(parse.str) && ft_strlen(expanded) == 0) || space_in_redir(parse.str, my_env))
	{
		ft_printf("AMBIGUOUS REDIRECT !\n");
		//ft_error("AMBIGUOUS REDIRECTION !");
		return (0);
	}
	if (access(expanded, F_OK | R_OK) == -1)
	{
		ft_printf("bash : %s\n", strerror(errno));
		return (0);
	}
	return (1);
}

char *expand_redirect(t_parse parse, t_list **my_env)
{
	char *expanded;

	expanded  = ft_strdup("");
	if (!env_in(parse.str))
		redir_without_quote(parse.str, &expanded);
	else
		do_expand(parse.str, my_env, &expanded);
	ft_printf("infile : %s\n", expanded);
	return (expanded);
}

int	env_in(char *str)
{
	int i;
	char quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else if (str[i] == '$' && quote != '\'' && str[i + 1] && \
			(ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
			return (1);
		i++;
	}
	return (0);
}

int space_in_redir(char *str, t_list **my_env)
{
	int i;
	char quote;
	char *value;

	i = 0;
	quote = 0;
		ft_printf("TEST\n");
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else if (str[i] == '$' && quote == 0 && str[i + 1] && \
			(ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			value = ft_getenv(my_env, get_name_var(str, &i), 1);
			if (value && space_in(value, str, i))
				return (free(value), 1);
			free(value);
		}
		i++;
	}
	return (0);
}

int space_in(char *value, char *str, int i)
{
	int j;
	int	end;

	j = 0;
	end = ft_strlen(value);
	if (!str[i] || str[i] != ' ' || str[i] != '\t')
		end = last_char_in_value(value);
	while (value[j] && j <= end)
	{
		ft_printf("char infile : %c end : %d j : %d\n",value[j], end , j);
		if (value[j] == ' ' || value[j] == '\t')
			return (1);
		j++;
	}
	return (0);
}

int last_char_in_value(char *str)
{
	int i;
	
	i = ft_strlen(str) - 1;
	ft_printf("last char '%c'\n",str[i]);
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	return (i);
}

void	redir_without_quote(char *str, char **expanded)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		ft_printf("str char : %c\n", str[i]);
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			*expanded = ft_strjoin2(*expanded, char_to_str(str[i]));
		i++;
	}
	ft_printf("expanded without quote : %s\n", *expanded);
}

void	do_expand(char *str, t_list **my_env, char **expanded)
{
	int i;
	char quote;
	char *value_env;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '$' && quote != '\'' && str[i + 1] && \
			(ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			if (str[i + 1] == '?')
			{
				*expanded = ft_strjoin2(*expanded, ft_itoa(g_errno));
				i += 2;
			}
			else
			{
				value_env = ft_getenv(my_env, get_name_var(str, &i), 1);
				if (!value_env)
					value_env = ft_strdup("");
				*expanded = ft_strjoin2(*expanded, value_env);
			}
		}
		else if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			i++;
		}
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
		{
			*expanded = ft_strjoin2(*expanded, char_to_str(str[i]));
			i++;
		}
	}
}

char *get_name_var(char *str, int *i)
{
	char *name;

	name = ft_strdup("");
	*i += 1;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		name = ft_strjoin2(name, char_to_str(str[*i]));
		*i += 1;
	}
	ft_printf("name var : %s\n", name);
	return (name);
}