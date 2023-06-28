/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:16:40 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 11:41:50 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Calculates the length of a string excluding characters within quotes.
 *
 * @param arg The input string to calculate the length of.
 */
static int	len_quoteless(char *arg)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	quote = 0;
	len = 0;
	while (arg[++i])
	{
		if (ft_strchr("\"\'", arg[i]) && !quote)
		{
			quote = arg[i];
			len--;
		}
		else if (ft_strchr("\"\'", arg[i]) && quote == arg[i])
		{
			len--;
			quote = 0;
		}
		len++;
	}
	return (len);
}

/**
 * Checks and updates the state of quotes in a string.
 *
 * @param arg The input string.
 * @param i A pointer to the current index in the string.
 * @param quote A pointer to the current quote character.
 */
static void	quote_checker(char *arg, int *i, char *quote)
{
	if (ft_strchr("\"\'", arg[*i]) && !*quote)
		*quote = arg[*i];
	else if (ft_strchr("\"\'", arg[*i]) && *quote == arg[*i])
		*quote = 0;
}

/**
 * Removes quotes from a string and returns the modified string.
 *
 * @param arg The input string.
 * @return Returns a new string with quotes removed.
 */
char	*quote_remover(char *arg)
{
	char	*res;
	char	quote;
	int		i;
	int		j;

	i = -1;
	j = 0;
	quote = 0;
	if (len_quoteless(arg) <= 0)
	{
		free(arg);
		return (ft_strdup(""));
	}
	res = ft_calloc(len_quoteless(arg) + 1, sizeof(char));
	while (arg[++i])
	{
		quote_checker(arg, &i, &quote);
		if (i > (int)ft_strlen(arg) - 1)
			break ;
		if ((quote && quote != arg[i]) || (!quote && !ft_strchr("\"\'", arg[i])))
			res[j++] = arg[i];
	}
	return (res[j] = 0, free(arg), res);
}
