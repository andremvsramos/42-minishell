/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:10:05 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/05 11:31:52 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	check_exit(t_minishell *ms, char *cmd)
{
	int	status;

	(void)cmd;
	wait(&status);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	if (g_exit != 1)
	{
		free_program(ms, 1);
		exit (g_exit);
	}
}
