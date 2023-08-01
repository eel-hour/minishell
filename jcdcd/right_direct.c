/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_direct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 22:36:10 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/29 18:46:13 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int direct(char **ptr, t_struct *s)
{
    int i;
    int trigger;

    i = 0;
    trigger = 0;
    while (ptr[i] && ptr[i][0] != '>' && ptr[i][0] != '<')
        i++;
    if (ptr[i][0] == '>')
    {
        if (trigger == 0)
        {
            trigger = 1;
            redirections(ptr, s);
        }
    }
    if (ptr[i][0] == '<')
    {
        if (trigger == 0)
        {
            trigger = 1;
            create_file2(ptr, s);
        }
    }
    return (0);
}

int redirection(char **ptr, t_struct *s)
{
    if (direct(ptr, s) != 0)
        return (1);
    return (0);
}