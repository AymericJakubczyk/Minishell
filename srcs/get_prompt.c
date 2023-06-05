/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:22:21 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/01 17:22:23 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *replace_in_path(char *home, char *path)
{
    int i;

    i = 0;
    while (home[i] && path[i] && home[i] == path[i])
        i++;
    return (ft_strjoin("~", &path[i]));
}

int is_in_path(char *home, char *path)
{
    int i;

    i = 0;
    while (home[i] && path[i] && home[i] == path[i])
        i++;
    if (home[i] == '\0')
        return (1);
    else
        return (0);
}

char *ft_get_path(char **env)
{
    char *path;
    char *home;

    path = getenv("PWD");
    home = getenv("HOME");

    if (is_in_path(home, path))
        path = replace_in_path(home, path);
    //ft_printf(path);
    return (path);
}

char *ft_get_prompt(char **env)
{
    char *prompt;
    char *user;
    char *path;

    user = getenv("USER");
    path = ft_get_path(env);
    prompt = ft_strjoin(user, ":");
    prompt = ft_strjoin(prompt, path);
    prompt = ft_strjoin(prompt, "$ ");
    return (prompt);
}