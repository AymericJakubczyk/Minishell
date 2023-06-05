/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:11:04 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/06/01 14:11:05 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int main(int ac, char **av ,char **env)
{
    char *str;

    printf("pwd : %s\n",getenv("PWD"));
    str = ft_strdup("");
    while (ft_strcmp(str, "exit") != 0)
    {
        free(str);
        str = readline(ft_get_prompt(env));
        //printf(ft_get_prompt(env));
        add_history(str);
        printf("cmd : %s\n", str);
        //exec_cmd();
    }
    free(str);
}


