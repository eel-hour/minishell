/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:06:23 by eel-hour          #+#    #+#             */
/*   Updated: 2023/07/07 18:48:24 by eel-hour         ###   ########.fr       */
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

	if (single_quotes(str) == 1 || double_quotes(str) == 1)
		return (1);
	i = 0;
	error_found = 0;
	
	return (error_found);
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

	// if (error(str) != 0)
	// 	exit(0);
		//ana drt exit hna nta ghadir return chi 9lwa bach tl3 command prompt again
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
	
	char p[30] = "\"pwd\"\">\"\"po\"\0";
	printf("%d\n", redirect_count(p));
	// printf("%d\n\n", count(argv[1]));
	// char **parc = parcer(p);
	// while (parc[i] != 0)
	// {
	// 	printf("%s\n", parc[i]);
	// 	i++;
	// }
}

