/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-hour <eel-hour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:06:23 by eel-hour          #+#    #+#             */
/*   Updated: 2023/07/24 21:05:46 by eel-hour         ###   ########.fr       */
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
		else if ((str[i] >= 33 && str[i] <= 126) && str[i] != 62 && str[i] != 34 && str[i] != 39 && str[i] != ' ' && str[i] != '|' && str[i] != '\t' && redir == 1)
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
		else if ((str[i] >= 33 && str[i] <= 126) && str[i] != 60 && str[i] != 34 && str[i] != 39 && str[i] != ' ' && str[i] != '|' && str[i] != '\t' && redir == 1)
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

int curshs(char *str)
{
	int i;
	int cr;

	i = 0;
	cr = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '{' && cr == 0)
			cr++;
		else if (str[i] == '}' && cr == 1)
			cr--;
		i++;
	}
	if (cr == 0)
		return (0);
	else
		return (1);
}

int piipe(char *str)
{
	int i;
	int pp;

	i = 0;
	pp = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\0' && str[i] == '|' && str[i + 1] == '|')
			return (1);
		// else if (str[i] == '|' && pp == 0)
		// 	pp++;
		// else if ((str[i] >= 33 && str[i] <= 126) && str[i] != 60 && str[i] != 62 && str[i] != ' ' && str[i] != '\t' && pp == 1)
		// 	pp--;
		i++;
	}
	if (pp == 0)
		return (0);
	else
		return (1);
}

int error(char *str)
{
	if (single_quotes(str) == 1 || double_quotes(str) == 1 || fw_redir(str) == 1 || bw_redir(str) == 1 || piipe(str) == 1 || curshs(str) == 1)
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


char *joining(char **str)
{
	char *returnd;
	int i;

	returnd = "\0";
	i = 0;
	while (str[i])
	{
		returnd = ft_strjoin(returnd, str[i], 4);
		i++;
	}
	return (returnd);

}

char **replacing(char **str, t_struct *s)
{
	int i;
	int k;
	
	i = 0;
	k = 0;
    while (str[i])
    {
		// if ((ft_strlen(str[i]) >= 5) && str[i][0] == '$' && str[i][1] == 'P' && str[i][2] == 'A' && str[i][3] == 'T' && str[i][4] == 'H' && str[i][5] == '\0')
		// 	;
		if (ft_strcmp(str[i], "$PATH", -1))
			str[i] = ft_strdup()
        /*else */if (str[i][0] == '$' && getenv(path(str[i])) != NULL)
            str[i] = remove_nl(getenv(path(str[i])));
		else if (str[i][0] == '$')
		{
            k = i;
			while (str[i])
			{
				str[i] = str[i + 1];
				i++;
			}
			i = k;
			i--;
		}
		else
			str[i] = str[i];
        i++;
    }
	return (str);
}

char *replace_pwd(char *str, t_struct *s)
{
	int i;
	int trigger;
	char	**returnd;

	trigger = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			trigger = 1;
		i++;
	}
	if (trigger)
	{
		returnd = ft_spliting(str);
		returnd = replacing(returnd, s);
		return (joining(returnd));
	}
	else
	{
		return (str);
	}
}

char **check_path(char **str, t_struct *s)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i][0] != '\'' && str[i][ft_strlen(str[i]) - 1] != '\'')
			str[i] = replace_pwd(str[i], s);
		i++;
	}
	return (str);
}

char **remove_single(char **str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == '\'' && str[i][ft_strlen(str[i]) - 1] == '\'')
		{
			j = 0;
			while (str[i][j])
			{
				str[i][j] = str[i][j +1];
				j++;
			}
			str[i][j - 2] = str[i][j - 1];
		}
		i++;
	}
	return (str);
}

char **parser(char *str, t_struct *s)
{
	t_parsing	data;
	int 		history_a;
	int 		history_b;
	int			isecond;
	int			trig;
	int			i;

	if (error(str) == 1)
	{
		printf("parsing error!\n");
		return (double_char_null());
	}
	if (count(str) == 0)
		return (NULL);
	data.parsed = malloc(sizeof(char*) * (count(str) + 1));
	i = 0;
	data.k = 0;
	isecond = 0;
	history_a = 0;
	history_b = 0;
	trig = 0;
	data.cursh = 0;
	data.paran = 0;
	while (str[i] != '\0')
    {
		data.sub_a = 0;
		data.sub_b = 0;
		trig = 0;
		if (str[i] == '{')
		{
			data.cursh++;
			i++;
        }
		else if (str[i] == '(')
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
			data.sub_a = i;
			isecond = i;
			isecond++;
			while (str[isecond] != '\'')
			{
				if (str[isecond] == '$')
					trig = 1;
				isecond++;
			}
			if (trig)
			{
				i++;
				while (str[i] != '\'')
					i++;
				i++;
				data.sub_b = i;
				i++;
			}
			else
			{
				i++;
				data.sub_a = i;
				while (str[i] != '\'')
					i++;
				data.sub_b = i;
				i++;
			}
		}
        else
        {
			data.sub_a = i;
            while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '\"' && str[i] != '\'')
                i++;
			if (data.cursh == 1 && (str[i - 1] == '}' || str[i - 1] == ')') && data.paran == 1 && (str[i - 2] == '}' || str[i - 2] == ')'))
			{
				data.paran--;
				data.cursh--;
				data.sub_b = i - 2;
			}
			else if (data.cursh == 1 && str[i - 1] == '}')
			{
				data.cursh--;
				data.sub_b = i - 1;
			}
			else if (data.paran == 1 && str[i - 1] == ')')
			{
				data.paran--;
				data.sub_b = i - 1;
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
	data.parsed = check_path(data.parsed, s);
	data.parsed = remove_single(data.parsed);
	return (data.parsed);
}


// int main()
// {
// 	char p[100] = "$PATH";
// 	char **s = parser(p);
// 	int i = 0;
// 	while (s[i] != 0)
// 		printf("%s\n",s[i++]);
// }
