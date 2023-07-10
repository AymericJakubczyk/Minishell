

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_entry
{
	char	c;
	int		type;
	int		context;
}	t_entry;

typedef struct s_parse
{
	char	*str;
	int		type;
}	t_parse;

typedef struct s_exec
{
	int		nbr_limiter;
	char	**all_limiter;
	char	**str_heredoc;
	int		nbr_cmd;
	char	**env;
	int		fd_in;
	int		fd_out;
    int     pipes[2];
	int		prec_fd;
}	t_exec;

#endif