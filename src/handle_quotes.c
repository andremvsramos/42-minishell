/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:16:40 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/30 15:52:36 by marvin           ###   ########.fr       */
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
