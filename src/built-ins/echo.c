/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:15:06 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/28 12:46:20 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Check the end of a line and determine whether to print a newline or space.
 *
 * @param input  The input string.
 * @param n      A boolean flag indicating whether a newline is expected.
 * @return       0 if newline should be printed, 1 if space should be printed.
 */
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

/**
 * Print the arguments passed to the echo command.
 *
 * @param input  An array of strings representing the arguments.
 * @param n      A boolean flag indicating whether the -n option is present.
 * @param i      The starting index of the arguments to be printed.
 */
static void	echo_print(char **input, bool n, int i)
{
	while (input[i])
	{
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

/**
 * Handle errors encountered during the execution of the echo command.
 *
 * @param ms     A pointer to the t_minishell struct.
 * @param input  An array of strings representing the command arguments.
 */
static void	handle_error_echo(t_minishell *ms, char **input)
{
	printf("\n");
	free_child(ms, input, 0);
	g_exit = 0;
	exit (0);
}

/**
 * Execute the echo command.
 *
 * @param ms     A pointer to the t_minishell struct.
 * @param input  An array of strings representing the command arguments.
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
