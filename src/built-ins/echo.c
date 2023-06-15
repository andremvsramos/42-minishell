/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:15:06 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/15 09:50:36 by tsodre-p         ###   ########.fr       */
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
		//input[i] = ft_strtrim(input[i], "\'\"");
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

static void	handle_error_echo(t_minishell *ms, char **input)
{
	printf("\n");
	free_child(ms, input, 0);
	g_exit = 0;
	exit (0);
}

/*
Echo prints text:
-n flag doesn't output a newline on prompt
or on the file to be outputten
*/
void	do_echo(t_minishell *ms, char **input)
{
	int		i;
	bool	n;

	n = false;
	i = 0;
	while (input[i])
		i++;
	if (i <= 1)
		handle_error_echo(ms, input);
	else if (input[1][0] == '-' && input[1][1] == 'n' && !input[2])
		return ;
	i = 1;
	if (check_strcmp("-n", input[i]))
	{
		n = true;
		i++;
	}
	echo_print(input, n, i);
	free_child(ms, input, 0);
	g_exit = 0;
	exit (0);
}
