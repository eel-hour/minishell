/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:06:02 by eel-hour          #+#    #+#             */
/*   Updated: 2023/07/24 23:50:16 by eel-hour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// int	ft_str2len(char **chart)
// {
// 	int	i;

// 	i = 0;
// 	while (chart[i] != '\0')
// 		i++;
// 	return (i);
// }

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

// void	*ft_calloc(unsigned int size, unsigned int len)
// {
// 	int				i;
// 	int				total;
// 	unsigned char	*ret;

// 	i = 0;
// 	total = size * len;
// 	ret = malloc(total);
// 	while (i < total)
// 	{
// 		ret[i] = '\0';
// 		i++;
// 	}
// 	return (ret);
// }

// void	ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*p;
// 	size_t			i;

// 	p = (unsigned char *)s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		p[i] = '\0';
// 		i++;
// 	}
// }

// int	ft_atoi(char *nptr)
// {
// 	int	sign;
// 	long	value;
// 	int	i;

// 	i = 0;
// 	sign = 1;
// 	value = 0;
// 	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
// 		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
// 		i++;
// 	if (nptr[i] == '-')
// 	{
// 		sign = sign * (-1);
// 		i++;
// 		if (nptr[i] == '-' || nptr[i] == '+')
// 			return (0);
// 	}
// 	if (nptr[i] == '+')
// 		i++;
// 	while (ft_isdigit(nptr[i]))
// 		value = value * 10 + (nptr[i++] - 48);
// 	if (value * sign > 2147483647 || value * sign < -2147483648)
// 	{
// 		write(2, "Error\n", 6);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (value * sign);
// }

size_t	counting(char *s)
{
	size_t	i;
	size_t	co;

	i = 0;
	co = 0;
	while (s[i])
	{
		while (s[i] == '$' || s[i] == '/')
			i++;
		if (s[i])
			co++;
		while ((s[i] != '$' && s[i] != '/') && s[i])
			i++;
	}
	return (co);
}

// char	*ft_strjoin_1(char *s1, char *s2)
// {
// 	char	*ret;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (!s1)
// 		s1 = ft_calloc(1, 1);
// 	if (!s2 || !s1)
// 		return (NULL);
// 	ret = ft_calloc(1, (ft_strlen(s1) + ft_strlen(s2) + 2));
// 	if (!ret)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		ret[i] = s1[i];
// 		i++;
// 	}
// 	ret[i] = ' ';
// 	i++;
// 	while (s2[j] != '\0')
// 		ret[i++] = s2[j++];
// 	free(s1);
// 	return (ret);
// }


// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	unsigned int	j;
// 	char			*str;
// 	unsigned int	i;

// 	i = ft_strlen(s);
// 	if (start > i)
// 		return (ft_calloc(1, 1));
// 	if (len > i)
// 		len = i - start;
// 	if (!s)
// 		return (0);
// 	j = 0;
// 	str = malloc(len + 1);
// 	if (!str)
// 		return (NULL);
// 	while (j < len && start < i)
// 	{
// 		str[j] = s[j + start];
// 		j++;
// 	}
// 	str[j] = '\0';
// 	return (str);
// }

char	**ft_spliting(char *s)
{
	char	**trimmed;
	size_t	i;
	size_t	j;
	size_t	a;
	size_t	b;

	trimmed = malloc((counting(s) + 2) * 8);
	if (!trimmed)
		return (0);
	i = 0;
	j = 0;
	while (s[i] && j < (counting(s) + 1))
	{
		a = 0;
		b = 0;
		while (s[i] == '$' || s[i] == '/' || s[i] == '+')
			i++;
		a = i;
		if (i != 0)
			a = i - 1;
		while ((s[i] != '$' && s[i] != '/' && s[i] != '+') && s[i])
			i++;
		b = i;
		trimmed[j++] = ft_substr(s, a, (b - a));
	}
	trimmed[j] = 0;
	return (trimmed);
}

