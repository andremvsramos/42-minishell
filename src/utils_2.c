/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:03:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/05/31 16:14:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	get_exit_status(t_minishell *ms)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	status = 0;
	while (i < ms->n_cmd)
	{
		signal(SIGINT, &handler_sigint);
		pid = waitpid(ms->pid[i++], &status, 0);
		if (pid < 0)
			continue ;
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit = 128 + WTERMSIG(status);
	}
}
