/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 23:14:14 by hben-bou          #+#    #+#             */
/*   Updated: 2023/07/22 19:21:03 by eel-hour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define FD_ERROR "ERROR INITIALIZING FILE DESCIPTOR\n"
#define DUP_ERROR "ERROR DUPLICATING FILE\n"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char **environ;

typedef struct s_struct
{
    char *PATH;
    int pid;
	int exit_status;
} t_struct;

typedef struct data_struct
{
	char 	**parsed;
	int	k;
	int  sub_a;
	int  sub_b;
	int		cursh;
	int		paran;
}			t_parsing;

char	*ft_substr(char *s, int start, int len);
char	**ft_spliting(char *s);

// --error checker
int error(char *str);
// --likatssb lik >,>>,<,<<
int redirect_count(char *str);
// --hada lparser
char **parser(char *str);
// --ft_split--
char **ft_split(char *str, char c);
// --utils--
int ft_strlen(char *str);
int ft_strcmp(char *s1, char *s2, int len);
int check_commands(char **str, t_struct *s);
char *ft_strdup(char *str);
void ft_putstr(char *str);
// --redirection
int redirection(char **ptr, t_struct *s);
// --main--
int commands(char **str);
char *join(char *str);
// --environment--
void export(char *str);
void unset(char *str);
void declare_x(void);
// --path--
void	get_path(char **str);
char *path(char *str);
char *remove_nl(char *str);
// --parser--
int redirection_counter(char **str);
char **no_redir(char **parsed);
char **parser(char *str);
// --heredoc--
char *heredoc(char *str);
char *ft_strjoin(char *s1, char *s2, int type);
// --left_direct--
char *read_file(int fd);
// --create_files--
void create_files(char **ptr, t_struct *s);
int *create_file2(char **ptr, t_struct *s);
int execute(int *fd, char **ptr, t_struct *s);
// --old_pwd--
void old_pwd(void);
void new_pwd(void);
// --echo--
void pwd(void);
void echo(char **str, t_struct *s);
void cd(char **str);
void print_env(void);
// --builtins--
void dollar(char **ptr);
#endif