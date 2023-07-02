/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:06:23 by eel-hour          #+#    #+#             */
/*   Updated: 2023/07/02 02:56:57 by eel-hour         ###   ########.fr       */
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
		return (ft_calloc(1, 1));
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

// int error(char *str)
// {
// 	int i;
// 	int error_found;

// 	i = 0;
// 	error_found = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\'')
// 		{
// 			while (str[i] != '\0')
// 			{
// 				i++;
// 				if (str[i] == '\'')
// 					break;
// 			}
// 		}
// 		i++;
// 	}
// }

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

char **parcer(int counted, char *str)
{
	char 	**parced;
	size_t	i;
	size_t	k;
	size_t  sub_a;
	size_t  sub_b;
  
	parced = malloc(sizeof(char**) * counted);
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
		if ((sub_b - sub_a) > 0 && k < counted)
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
	// printf("%s", argv[1]);
	// printf("%d\n\n", count(argv[1]));
	char **parc = parcer(count(argv[1]), argv[1]);
	while (parc[i] != 0)
	{
		printf("%s\n", parc[i]);
		i++;
	}
}

