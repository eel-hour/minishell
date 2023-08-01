/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:06:02 by eel-hour          #+#    #+#             */
/*   Updated: 2023/07/25 02:29:01 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	counting(char *s)
{
	int	i;
	int	co;

	i = 0;
	co = 0;
	while (s[i])
	{
		while (s[i] == '$' || s[i] == '/' || s[i] == '+')
			i++;
		if (s[i])
			co++;
		while ((s[i] != '$' && s[i] != '/' && s[i] != '+') && s[i])
			i++;
	}
	return (co);
}


char	**ft_spliting(char *s)
{
	char	**trimmed;
	int	i;
	int	j;
	int	a;
	int	b;

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