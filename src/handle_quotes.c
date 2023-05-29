/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:16:40 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/29 11:43:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Check how many single quotes there is int the string
int	count_quotes(char *input, char quote)
{
	int	i;
	int	num_quotes;

	i = 0;
	num_quotes = 0;
	while (input[i])
	{
		if (input[i] == quote)
			num_quotes++;
		i++;
	}
/* 	if (num_quotes % 2 != 0)
	{
		printf("%s", "Error: unclosed quotes");

		//handler(SIGINT);
	} */
	return (num_quotes);
}

int	handle_quotes(char *input)
{
	size_t	i;
	int		quotes;

	i = 0;
	quotes = 0;
	if(input[0] == '\'' || input[ft_strlen(input) - 1] == '\'')
		quotes = count_quotes(input, '\'');
	else if (input[0] == '"' || input[ft_strlen(input) - 1] == '"')
		quotes = count_quotes(input, '"');
	if (!quotes)
	{
		while (i <= (ft_strlen(input)))
			printf("%c", input[i++]);
	}
	else
	{
		while (++i <= (ft_strlen(input) - 2))
			printf("%c", input[i]);
	}
	return (0);
    /*export abc=123
      echo $abc
	  >>> 123
	*/
}
