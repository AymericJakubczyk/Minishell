/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:34:51 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/07/18 14:35:31 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_heredoc(t_exec *data, int num_cmd);

int	redirect_in_cmd(t_parse *parse, int mode)
{
	int	i;

	i = 0;
	while (mode == IN && parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == HEREDOC || parse[i].type == REDIRECT_IN)
			return (1);
		i++;
	}
	while (mode == OUT && parse[i].str && parse[i].type != PIPEE)
	{
		if (parse[i].type == REDIRECT_OUT || parse[i].type == APPEND)
			return (1);
		i++;
	}
	return (0);
}

void	do_classique_pipe(int num_cmd, t_exec *data, int mode)
{
	close(data->pipes[0]);
	if (mode == IN && num_cmd > 0)
		dup2(data->prec_fd, STDIN_FILENO);
	if (mode == OUT && num_cmd < data->nbr_cmd - 1)
		dup2(data->pipes[1], STDOUT_FILENO);
}

void	do_redirect_in(t_parse *parse, t_list **my_env, \
t_exec *data, int num_cmd)
{
	char	*infile;
	int		fd;

	infile = get_last_file(parse, my_env, IN);
	if (last_redir(parse, IN) == HEREDOC)
		redirect_heredoc(data, num_cmd);
	else
	{
		fd = open(infile, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
}

void	do_redirect_out(t_parse *parse, t_list **my_env, t_exec *data)
{
	char	*outfile;
	int		fd;

	(void) data;
	outfile = get_last_file(parse, my_env, OUT);
	if (last_redir(parse, OUT) == REDIRECT_OUT)
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
}

static void	redirect_heredoc(t_exec *data, int num_cmd)
{
	int		pipes[2];
	char	*str;

	pipe(pipes);
	str = ft_get_str_hd(data->parse, data, num_cmd + 1);
	write(pipes[1], str, ft_strlen(str));
	close(pipes[1]);
	if (dup2(pipes[0], STDIN_FILENO) == -1)
		ft_printf("Dup2 problem\n");
}
