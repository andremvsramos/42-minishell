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

/**
 * Counts the number of words in a string based on a given delimiter character.
 *
 * @param str The input string.
 * @param c   The delimiter character.
 *
 * @return Returns the number of words in the string.
 */
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

/**
 * Computes the length of a word in a string based on a given delimiter
 * character.
 *
 * @param str The input string.
 * @param c   The delimiter character.
 *
 * @return Returns the length of the word.
 */
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

/**
 * Extracts a word from a string based on a given delimiter character and stores
 * it in the words array.
 * The function also considers if there are quotes on the string.
 *
 * @param s     The input string.
 * @param c     The delimiter character.
 * @param words Pointer to the words array.
 *
 * @return Returns a pointer to the remaining portion of the string after
 * the extracted word.
 */
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

/**
 * Splits a string into an array of strings based on a given
 * delimiter character.
 * This function is used instead of ft_split as the latter does not take
 * into account double or single quotes.
 *
 * @param s The input string to be split.
 * @param c The delimiter character.
 *
 * @return Returns an array of strings resulting from the split operation.
 */
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
