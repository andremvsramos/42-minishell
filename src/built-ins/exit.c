/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:10:05 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/12 12:46:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

static void	exit_error2(t_minishell *ms, char **cmd_query)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd_query[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	g_exit = 2;
	free_child(ms, cmd_query, 0);
	exit (g_exit);
}

static void	exit_error1(t_minishell *ms, char **cmd_query, int i)
{
	if (i == 2)
	{
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

void	do_exit(t_minishell *ms, char **cmd_query, int x)
{
	int	i;

	i = 0;
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
