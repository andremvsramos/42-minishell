/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:15:06 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/05/31 12:02:04 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_end(char *input, bool n)
{
	if (!input)
	{
		if (n == false)
			printf("\n");
		return (0);
	}
	else
		printf(" ");
	return (1);
}

static void	echo_print(char **input, bool n, int i)
{
	while (input[i])
	{
		input[i] = ft_strtrim(input[i], "\'\"");
		if (check_strcmp("$?", input[i]))
		{
			printf("%d", g_exit);
			if (!check_end(input[i + 1], n))
				break ;
		}
		else
		{
			printf("%s", input[i]);
			if (!check_end(input[i + 1], n))
				break ;
		}
		i++;
	}
}

/*
Echo prints text:
-n flag doesn't output a newline on prompt
or on the file to be outputten
*/
void	do_echo(char **input)
{
	int		i;
	bool	n;

	n = false;
	if (!input)
	{
		printf("\n");
		return ;
	}
	else if (input[1][0] == '-' && input[1][1] == 'n' && !input[2])
		return ;
	i = 1;
	input[i] = ft_strtrim(input[i], "\'\"");
	if (check_strcmp("-n", input[i]))
	{
		n = true;
		i++;
	}
	echo_print(input, n, i);
}