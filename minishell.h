/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 23:14:14 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/09 21:24:17 by eel-hour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char **environ;

typedef struct s_struct
{
    char    *PATH;
}           t_struct;

typedef struct data_struct
{
	char 	**parsed;
	size_t	i;
	size_t	k;
	size_t  sub_a;
	size_t  sub_b;
	int		cursh;
	int		paran;
}			t_parsing;

// --error checker
int error(char *str);
// --likatssb lik >,>>,<,<<
int redirect_count(char *str);
// --hada lparser
char **parser(char *str);
// --ft_split--
char **ft_split(char *str);
// --utils--
int ft_strlen(char *str);
int ft_strcmp(char *s1, char *s2, int len);
int check_commands(char **str, t_struct *s);
char *ft_strdup(char *str);
// --redirection
int redirection(char *path, char **ptr, int c);
// --main--
int commands(char **str);
char *join(char *str);
// --environment--
void export(char *str);
// --path--
int get_path(char **str);

#endif