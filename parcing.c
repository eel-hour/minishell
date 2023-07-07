/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:06:23 by eel-hour          #+#    #+#             */
/*   Updated: 2023/07/07 20:12:51 by eel-hour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(unsigned int size, unsigned int len)
{
	int				i;
	int				total;
	unsigned char	*ret;

	i = 0;
	total = size * len;
	ret = malloc(total);
	while (i < total)
	{
		ret[i] = '\0';
		i++;
	}
	return (ret);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	j;
	char			*str;
	unsigned int	i;

	i = ft_strlen(s);
	if (start > i)
		return ("\0");
	if (len > i)
		len = i - start;
	if (!s)
		return (0);
	j = 0;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (j < len && start < i)
	{
		str[j] = s[j + start];
		j++;
	}
	str[j] = '\0';
	return (str);
}

// hadi li kat7ssb dok ">>"

int redirect_count(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>')
		{
			i++;
			if (str[i] >= 21 && str[i] <= 126 && str[i] != '\0')
				i++;
			count++;
		}
		else if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
				i++;
			else if (str[i] >= 21 && str[i] <= 126 && str[i] != '\0')
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

int double_quotes(char *str)
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && quotes == 0)
			quotes++;
		else if (str[i] == '\"' && quotes == 1)
			quotes--;
		i++;
	}
	if (quotes == 0)
		return (0);
	else
		return (1);
}

int fw_redir(char *str)
{
	int i;
	int redir;

	i = 0;
	redir = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' && redir == 0)
		{
			if (str[i + 1] == '>')
				i++;
			redir++;
		}
		else if ((str[i] >= 33 && str[i] <= 126) && str[i] != 62 && str[i] != 34 && str[i] != 39 && str[i] != ' ' && str[i] != '\t' && redir == 1)
			redir--;
		i++;
	}
	if (redir == 0)
		return (0);
	else
		return (1);
}

int bw_redir(char *str)
{
	int i;
	int redir;

	i = 0;
	redir = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && redir == 0)
		{
			if (str[i + 1] == '<')
				i++;
			redir++;
		}
		else if ((str[i] >= 33 && str[i] <= 126) && str[i] != 60 && str[i] != 34 && str[i] != 39 && str[i] != ' ' && str[i] != '\t' && redir == 1)
			redir--;
		i++;
	}
	if (redir == 0)
		return (0);
	else
		return (1);
}

int single_quotes(char *str)
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && quotes == 0)
			quotes++;
		else if (str[i] == '\'' && quotes == 1)
			quotes--;
		i++;
	}
	if (quotes == 0)
		return (0);
	else
		return (1);
}

int error(char *str)
{
	int i;
	int error_found;

	if (single_quotes(str) == 1 || double_quotes(str) == 1 || fw_redir(str) == 1 || bw_redir(str) == 1)
		return (1);
	return (0);
}

int count(char *str)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ' || str[i] == '\t')
        {
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			else if (str[i] == '<' && str[i + 1] == '<')
				i++;
			count++;
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
			count++;
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			count++;
			i++;
		}
        else
        {
			count++;
            while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '\"' && str[i] != '\'')
                i++;
        }
    }
	return (count);
}

char **parser(char *str)
{
	char 	**parced;
	size_t	i;
	size_t	k;
	size_t  sub_a;
	size_t  sub_b;

	parced = malloc(sizeof(char**) * count(str));
	i = 0;
	k = 0;
	while (str[i] != '\0')
    {
		sub_a = 0;
		sub_b = 0;
        if (str[i] == ' ' || str[i] == '\t')
        {
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			sub_a = i;
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			else if (str[i] == '<' && str[i + 1] == '<')
				i++;
			i++;
			sub_b = i;
		}
		else if (str[i] == '\"')
		{
			i++;
			sub_a = i;
			while (str[i] != '\"')
				i++;
			sub_b = i;
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			sub_a = i;
			while (str[i] != '\'')
				i++;
			sub_b = i;
			i++;
		}
        else
        {
			sub_a = i;
            while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '\"' && str[i] != '\'')
                i++;
			sub_b = i;
        }
		if ((sub_b - sub_a) > 0 && k < count(str))
		{
			parced[k] = ft_substr(str, sub_a, sub_b - sub_a);
			k++;
		}
    }
	parced[k] = 0;
	return (parced);
}

int main(int argc, char **argv)
{
	int i = 0;
	
	char p[30] = "\"pwd\"\">\"\'po\'\0";
	printf("%d\n", error(p));
	// printf("%d\n", redirect_count(p));
	// printf("%d\n\n", count(argv[1]));
	// char **parc = parcer(p);
	// while (parc[i] != 0)
	// {
	// 	printf("%s\n", parc[i]);
	// 	i++;
	// }
}

