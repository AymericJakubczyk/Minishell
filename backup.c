/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:55:37 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/07 19:36:29 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quote(char *str, int runner, char quote);
int	skip_quote_and_fill(char *str, int runner, char quote, char *array);
void	fill_output(t_parse *array, char *str);
void	fill_tabs(t_parse *array, char *str);




void check_syntax_quote(char *str)
{
	int i;
	char quote;
	
	ft_printf("cmd test : %s!!\n", str);
	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == quote)
			quote = 0;
		else if (str[i] == '\'' && quote == 0)
			quote = '\'';
		else if (str[i] == '\"' && quote == 0)
			quote = '\"';
		i++;
	}
	if (quote != 0)
	{
		ft_printf("syntax error!\n");
		exit(2);
	}
	else
		ft_printf("good quote\n");
}

void	whitespaces_split(char *str)
{
	int	runner;
	int	count;
	t_parse	*output;

	runner = 0;
	count = 0;
	while (str[runner])
	{
		while (str[runner] && ((str[runner] != ' ') && (str[runner] != '\t') && (str[runner] != '|') && (str[runner] != '<') && (str[runner] != '>')))
		{
			if (str[runner] == '\'')
				runner = skip_quote(str, runner, '\'');
			if (str[runner] == '\"')
				runner = skip_quote(str, runner, '\"');
			runner++;
		}
		if (str[runner])
			count++;
		runner++;
	}
	ft_printf("%d\n", count);
	output = ft_calloc(sizeof(t_parse), count);
	fill_output(output, str);
}

void	fill_output(t_parse *array, char *str)
{
	int	runner;
	int	count;
	int	tmp;
	t_parse	*output;

	tmp = 0;
	runner = 0;
	count = 0;
	while (str[runner])
	{
		tmp = runner;
		while (str[runner] && ((str[runner] != ' ') && (str[runner] != '\t') && (str[runner] != '|') && (str[runner] != '<') && (str[runner] != '>')))
		{
			if (str[runner] == '\'')
				runner = skip_quote(str, runner, '\'');
			if (str[runner] == '\"')
				runner = skip_quote(str, runner, '\"');
			runner++;
		}
		ft_printf("%d\n", (runner - tmp));
		array[count].str = malloc(sizeof(char *) * (runner - tmp + 1));
		count++;
		runner++;
	}
	fill_tabs(array, str);
}

void	fill_tabs(t_parse *array, char *str)
{
	int	runner;
	int	count;
	int	tmp;
	t_parse	*output;

	tmp = 0;
	runner = 0;
	count = 0;
	while (str[runner])
	{
		tmp = 0;
		while (str[runner] && ((str[runner] != ' ') && (str[runner] != '\t') && (str[runner] != '|') && (str[runner] != '<') && (str[runner] != '>')))
		{
			if (str[runner] == '\'')
				runner = skip_quote_and_fill(str, runner, '\'', &array[count].str[tmp]);
			if (str[runner] == '\"')
				runner = skip_quote_and_fill(str, runner, '\"', &array[count].str[tmp]);
			array[count].str[tmp] = str[runner];
			tmp++;
			runner++;
		}
		array[count].str[tmp] = '\0';
		ft_printf("%s\n", array[count].str);
		count++;
		runner++;
	}
}

int	skip_quote(char *str, int runner, char quote)
{
	while (str[runner] && str[runner] != quote)
		runner++;
	return (runner);
}

int	skip_quote_and_fill(char *str, int runner, char quote, char *array)
{
	int	index;

	index = 0;
	while (str[runner] && str[runner] != quote)
	{
		array[index] = str[runner];
		runner++;
	}
	return (runner);
}
