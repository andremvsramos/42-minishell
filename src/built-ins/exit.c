/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:10:05 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/28 12:41:13 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Check and process the exit command.
 * This function is called only when running a single command,
 * in this case, 'exit'.
 *
 * @param ms         The minishell structure.
 * @param cmd_query  The command query.
 */
void	check_exit(t_minishell *ms, char **cmd_query)
{
	int	i;
	int	status;

	i = 0;
	while (cmd_query[i])
		i++;
	wait(&status);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	if (g_exit != 1 || (g_exit == 1 && i == 2))
	{
		ft_free_split(cmd_query);
		free_program(ms, 1);
		exit (g_exit);
	}
}

/**
 * Handle the error condition for the exit command where
 * a numeric argument is required.
 *
 * @param ms         The minishell structure.
 * @param cmd_query  The command query.
 */
static void	exit_error2(t_minishell *ms, char **cmd_query)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd_query[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	g_exit = 2;
	free_child(ms, cmd_query, 0);
	exit (g_exit);
}

/**
 * Handle the error conditions for the exit command.
 * If i is 2, it checks if the argument cmd_query[1] is a
 * valid numeric argument. If it is, it calculates the exit status
 * by taking the modulus of the numeric value with 256, sets the
 * global g_exit variable to the calculated exit status.
 * The argument cmd_query[1] needs to be within LONG LONG value range.
 *
 * @param ms         The minishell structure.
 * @param cmd_query  The command query.
 * @param i          The number of arguments.
 */
static void	exit_error1(t_minishell *ms, char **cmd_query, int i)
{
	int	nbrlen;

	nbrlen = 0;
	if (i == 2)
	{
		nbrlen = ft_nbrlen(ft_atoll(cmd_query[1]));
		if (cmd_query[1][0] == '+')
			nbrlen++;
		if ((int)ft_strlen(cmd_query[1]) != nbrlen)
			exit_error2(ms, cmd_query);
		g_exit = (ft_atoi(cmd_query[1]) % 256);
		free_child(ms, cmd_query, 0);
		exit (g_exit);
	}
	else
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit = 1;
		free_child(ms, cmd_query, 0);
		exit (1);
	}
}

/**
 * Handle the "exit" command in the minishell.
 *
 * @param ms         The minishell structure.
 * @param cmd_query  The command query.
 * @param x          Indicator whether to display the "exit" message.
 */
void	do_exit(t_minishell *ms, char **cmd_query, int x)
{
	int	i;

	i = 0;
	if (ms->n_pipe > 0)
		x = 0;
	while (cmd_query[i])
		i++;
	if (x == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (i > 1)
	{
		if (ft_isnumeric(cmd_query[1]))
			exit_error1(ms, cmd_query, i);
		else
			exit_error2(ms, cmd_query);
	}
	else
	{
		free_child(ms, cmd_query, 0);
		exit(g_exit);
	}
}
