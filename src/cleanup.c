/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:14:01 by marvin            #+#    #+#             */
/*   Updated: 2023/05/31 16:14:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_program(t_minishell *ms, int i)
{
	free(ms->pid);
	unlink(".heredoc");
	if (ms->paths)
		ft_free_split(ms->paths);
	if (ms->args)
		ft_free_split(ms->args);
	if (i == 1)
		ft_free_lst(ms->env);
}

void	free_child(t_minishell *ms, char **cmd_query, int i)
{
	if (cmd_query)
		ft_free_split(cmd_query);
	unlink(".heredoc");
	if (ms->paths)
		ft_free_split(ms->paths);
	if (ms->query)
		ft_free_split(ms->query);
	if (ms->args)
		ft_free_split(ms->args);
	ft_free_lst(ms->env);
	free(ms->pid);
	ft_free_lst(ms->xprt);
	if (i == 1)
	{
		g_exit = 1;
		exit (1);
	}
}
