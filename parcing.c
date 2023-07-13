/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:06:23 by eel-hour          #+#    #+#             */
/*   Updated: 2023/07/13 19:35:20 by eel-hour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_strlen(char *str)
// {
//     int i;

//     i = 0;
//     while (str[i])
//         i++;
//     return (i);
// }

char **no_redir(char **parsed)
{
	int i;
	int j;
	int nofr;
	char **returnd;

	returnd = parsed;
	i = 0;
	j = 0;
	while (parsed[i])
	{
		if (parsed[i][0] == '<' || parsed[i][0] == '>')
			i++;
		returnd[j++] = parsed[i++];
	}
	returnd[j] = 0;
	return(returnd);
}

int redirection_counter(char **str)
{
	int i;
	int counter;
	
	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i][0] == '>' || str[i][0] == '<')
			counter++;
		i++;
	}
	return (counter);
}

void	*ft_calloc(int size, int len)
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

char	*ft_substr(char *s, int start, int len)
{
	int	j;
	char			*str;
	int	i;

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

// int curshs(char *str)
// {
// 	int i;
// 	int cr;

// 	i = 0;
// 	cr = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '{' && cr == 0)
// 			cr++;
// 		else if (str[i] == '}' && cr == 1)
// 			cr--;
// 		i++;
// 	}
// 	if (cr == 0)
// 		return (0);
// 	else
// 		return (1);
// }

int piipe(char *str)
{
	int i;
	int pp;

	i = 0;
	pp = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (1);
		else if (str[i] == '|' && pp == 0)
			pp++;
		else if ((str[i] >= 33 && str[i] <= 126) && str[i] != 60 && str[i] != 62 && str[i] != ' ' && str[i] != '\t' && pp == 1)
			pp--;
		i++;
	}
	if (pp == 0)
		return (0);
	else
		return (1);
}

int double_par(char *str)
{
	int i;
	int para_nmb;
	
	i = 0;
	para_nmb = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			para_nmb++;;
		i++;
	}
	if (para_nmb > 1)
		return (1);
	return (0);
}

int opend_n_closed(char *str)
{
	int i;
	int para_nmb;

	i = 0;
	para_nmb = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			para_nmb++;;
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ')')
			para_nmb--;;
		i++;
	}
	if (para_nmb != 0)
		return (1);
	return (0);
}

int error(char *str)
{
	if (single_quotes(str) == 1 || double_quotes(str) == 1 || fw_redir(str) == 1 || bw_redir(str) == 1 || piipe(str) == 1 || double_par(str) == 1 || opend_n_closed(str) == 1/* || curshs(str) == 1*/)
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

char **double_char_null(void)
{
	char **returnd;

	returnd = malloc(8);
	returnd[0] = 0;
	return (returnd);
}

char **parser(char *str)
{
	t_parsing	data;
	int		i;

	if (count(str) == 0)
		return (NULL);
	if (error(str) == 1)
	{
		printf("parsing error!\n");
		return (NULL);
	}
	data.parsed = malloc(sizeof(char*) * (count(str) + 1));
	i = 0;
	data.k = 0;
	data.cursh = 0;
	data.paran = 0;
	while (str[i] != '\0')
    {
		data.sub_a = 0;
		data.sub_b = 0;
		// if (str[i] == '{')
		// {
		// 	data.cursh++;
		// 	i++;
        // }
		if (str[i] == '(' && data.paran != 1)
		{
			data.paran++;
			i++;
        }
		else if (str[i] == ' ' || str[i] == '\t')
        {
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			data.sub_a = i;
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			else if (str[i] == '<' && str[i + 1] == '<')
				i++;
			i++;
			data.sub_b = i;
		}
		else if (str[i] == '\"')
		{
			i++;
			data.sub_a = i;
			while (str[i] != '\"')
				i++;
			data.sub_b = i;
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			data.sub_a = i;
			while (str[i] != '\'')
				i++;
			data.sub_b = i;
			i++;
		}
        else
        {
			data.sub_a = i;
            while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '\"' && str[i] != '\'')
                i++;
			// if (data.cursh == 1 && (str[i - 1] == '}' || str[i - 1] == ')') && data.paran == 1 && (str[i - 2] == '}' || str[i - 2] == ')'))
			// {
			// 	data.paran--;
			// 	data.cursh--;
			// 	data.sub_b = i - 2;
			// }
			// else if (data.cursh == 1 && str[i - 1] == '}')
			// {
			// 	data.cursh--;
			// 	data.sub_b = i - 1;
			// }
			if (data.paran != 0 && str[i - 1] == ')')
			{
				data.sub_b = i - data.paran;
				data.paran = 0;
			}
			else
				data.sub_b = i;
        }
		if ((data.sub_b - data.sub_a) > 0 && data.k < count(str))
		{
			data.parsed[data.k] = ft_substr(str, data.sub_a, data.sub_b - data.sub_a);
			data.k++;
		}
    }
	data.parsed[data.k] = 0;
	return (data.parsed);
}

// int main()
// {
// 	char p[100] = "{pwd}";
// 	// printf("%d", error(p));
// 	char **s = parser(p);
// 	int i = 0;
// 	while (s[i] != 0)
// 		printf("%s\n",s[i++]);
// }