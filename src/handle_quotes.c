/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:16:40 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/25 16:46:35 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Check how many single quotes there is int the string
static int	count_quotes(char *input, char quote)
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
	if (num_quotes % 2 != 0)
	{
		printf("%s", "Error: unclosed quotes");

		//handler(SIGINT);
	}
	return (num_quotes);
}

void	handle_quotes(char *input)
{
    size_t i;
	int		q;

	i = 0;
    q = 0;
	//printf("ISTO %c\n", input[ft_strlen(input) - 1]);
	if(input[0] == '\'' || input[ft_strlen(input) - 1] == '\'')
		q = count_quotes(input, '\'');
	else if (input[0] == '"' || input[ft_strlen(input) - 1] == '"')
		q = count_quotes(input, '"');
	if (input[1] == '$' && input[2] == '?' && ft_strlen(input) == 2)
    {
        printf("%d\n", g_exit);
		return ;
    }
	else
	{
        if (q == 0)
        {
            i = 0;
            while (i <= (ft_strlen(input)))
            {
                printf("%c", input[i]);
                i++;
            }
        }
        else
        {
            i = 1;
            while (i <= (ft_strlen(input) - 2))
            {
                printf("%c", input[i]);
                i++;
            }
        }
	}
}
