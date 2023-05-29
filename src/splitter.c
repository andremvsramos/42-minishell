/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:35:58 by marvin            #+#    #+#             */
/*   Updated: 2023/05/29 10:35:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_wordcounter(char *str, char c)
{
	int		i;
	int		wc;
	char	quote;

	i = 0;
	wc = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			wc++;
		while ((str[i] && str[i] != c) || (str[i] && quote))
		{
			quote = get_quote(str[i], quote);
			i++;
		}
	}
	return (wc);
}

int	ft_wordlen(char *str, char c)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while ((str[i] && (str[i] != c)) || (str[i] && quote))
	{
		quote = get_quote(str[i], quote);
		i++;
	}
	return (i);
}

static char	*get_word(char *s, char c, char **words)
{
	char	quote;

	quote = 0;
	*words = ft_substr(s, 0, ft_wordlen(s, c));
	while ((*s && *s != c) || (*s && quote))
	{
		quote = get_quote(*s, quote);
		s++;
	}
	return (s);
}

char	**splitter(char *s, char c)
{
	char	**split;
	int		wc;
	int		i;

	i = 0;
	if (!s)
		return (0);
	wc = ft_wordcounter(s, c);
	split = ft_calloc(wc + 1, sizeof(char *));
	if (!split)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			s = get_word(s, c, &split[i++]);
	}
	split[i] = 0;
	return (split);
}
