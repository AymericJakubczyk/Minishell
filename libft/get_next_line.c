/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:17:54 by ajakubcz          #+#    #+#             */
/*   Updated: 2022/12/15 18:02:55 by ajakubcz         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	check_backslash(char *buf, char **to_return);
static ssize_t	loop_read(int fd, char *buf, char **to_return);

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*to_return;
	ssize_t		check_ret_value;

	if (fd < 0 || read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
	{
		buf[0] = 0;
		return (NULL);
	}
	to_return = malloc(sizeof(char));
	if (to_return == 0)
		return (NULL);
	to_return[0] = '\0';
	if (ft_strlen(buf) != 0)
	{
		check_ret_value = check_backslash(buf, &to_return);
		if (check_ret_value == -1)
			return (NULL);
		if (check_ret_value == 1)
			return (to_return);
	}
	if (loop_read(fd, buf, &to_return) == -1)
		return (NULL);
	return (to_return);
}

static ssize_t	check_backslash(char *buf, char **to_return)
{
	ssize_t	i;

	i = backslash(buf);
	if (i != -1)
	{
		buf[i] = '\0';
		*to_return = ft_strjoin(*to_return, buf);
		if (*to_return == NULL)
			return (-1);
		setup_buf(buf, i);
		return (1);
	}
	*to_return = ft_strjoin(*to_return, buf);
	if (*to_return == NULL)
		return (-1);
	return (0);
}

static ssize_t	loop_read(int fd, char *buf, char **to_return)
{
	ssize_t		read_value;
	ssize_t		check_ret_value;

	read_value = read(fd, buf, BUFFER_SIZE);
	if (read_value == -1 || (read_value == 0 && ft_strlen(buf) == 0))
		return (free(*to_return), -1);
	buf[read_value] = '\0';
	while (read_value)
	{
		check_ret_value = check_backslash(buf, to_return);
		if (check_ret_value == -1 || check_ret_value == 1)
			return (read_value);
		read_value = read(fd, buf, BUFFER_SIZE);
		if (read_value == -1)
		{
			free(*to_return);
			return (-1);
		}
		buf[read_value] = '\0';
		if (read_value == 0)
			return (1);
	}
	buf[0] = 0;
	return (0);
}

#include <fcntl.h>
#include <stdio.h>
/*
int	main(int argc, char **argv)
{
	int	fd, fd2, fd3;
	(void) argc;
	char *txt;
	//char *str;
	int i;

	i = 0;
	printf("%d \n",argc);
	if(argc == 2)
		txt = argv[1];
	else
		txt = "test.txt";
	fd = open(txt, O_RDONLY);
	fd2 = open("tedfjkbdvjheb", O_RDONLY);
	fd3 = open("test2.txt", O_RDONLY);
	printf("BUFFER_SIZE : %d\n\n", BUFFER_SIZE);
	printf("%s==================================\n", get_next_line(fd));
	printf("%s==================================\n", get_next_line(fd));
	//printf("%s==================================\n", get_next_line(fd2));
	printf("%s==================================\n", get_next_line(fd3));
}
*/
