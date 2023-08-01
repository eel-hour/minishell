/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 22:36:10 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/30 02:27:28 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **direct_cmd(char **ptr)
{
    int i;
    char **str;

    i = 0;
    while (ptr[i] && operator(NULL, ptr[i]) != 2)
        i++;
    str = malloc(sizeof(char *) * i + 1);
    if (!str)
        return (NULL);
    i = 0;
    while (ptr[i] && operator(NULL, ptr[i]) != 2)
    {
        str[i] = ptr[i];
        i++;
    }
    str[i] = NULL;
    str[i++] = NULL;
    return (str);
}

int direct(char **ptr)
{
    int trigger;
    int *fd;
    int i;
    int k;
    int id;
    char *str;
    char **args;
    
    i = 0;
    k = 0;
    id = 0;
    trigger = 0;
    str = NULL;
    args = direct_cmd(ptr);
    fd = malloc(sizeof(int) * redirection_counter(ptr));
    if (!fd)
        return (-1);
    while (ptr[k] && ptr[k][0] != '>' && ptr[k][0] != '<')
        k++;
    k++;
    while (i < redirection_counter(ptr))
    {
        if (ptr[k - 1][0] == '>' && ptr[k - 1][1] == '\0')
            fd[i] = open(ptr[k], O_CREAT | O_RDWR | O_TRUNC,  0644);
        else if (ptr[k - 1][0] == '>' && ptr[k - 1][1] == '>')
            fd[i] = open(ptr[k], O_CREAT | O_RDWR | O_APPEND, 0644);
        else if (ptr[k - 1][0] == '<' && ptr[k - 1][1] == '<')
        {
            str = ft_strjoin(str, heredoc(ptr[k]));
            trigger = 1;
        }
        if (fd[i] < 0)
        {
            printf(FD_ERROR);
            return (-1);
        }
        i++;
        k += 2;
    }
    i = 0;
    return (0);
}

int heredocs(char **ptr)
{
    int i;
    int k;
    char **args;
    char *s;
    
    args = direct_cmd(ptr);
    i = 0;
    k = 0;
    while (ptr[k] && ptr[k][1] != '<')
        k++;
    while (i < redirection_counter(ptr))
    {
        if (ptr[k - 1][1] == '<' && ptr[k][2] == '\0')
            s = ft_strjoin(s, heredoc(ptr[k]));
        i++;
        k += 2;
    }
    exit(0);
    return (0);
}

int redirection(char **ptr)
{
    if (direct(ptr) != 0)
        return (1);
    return (0);
}