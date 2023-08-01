/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:48:52 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/21 02:11:56 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_putstr(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
        write(1, &str[i++], 1);
}
        
void sig_handler(int signals)
{
    if (signals == SIGINT)
    {
        rl_replace_line("\nminishell: ");
        rl_redisplay();
    }
}


int main()
{
    struct sigaction sa;

    int i = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sig_handler;
    while (1)
    {
        readline("minishell :");
        sigaction(SIGINT, &sa, NULL);
        int id = fork();
        if (id == 0)
        {
            pause();
            exit(1);
        }
        wait(NULL);
        i++;
    }
}