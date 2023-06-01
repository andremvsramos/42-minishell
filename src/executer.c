/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:12:20 by marvin            #+#    #+#             */
/*   Updated: 2023/05/29 11:12:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	exec_single_cmd(t_minishell *ms, char *cmd)
{
	char	**cmd_query;

	ms->pid[0] = fork();
	if (!ms->pid[0])
	{
		cmd_query = handle_redirects(ms, cmd);
		parse_query(ms, cmd_query);
	}
}

void	execute(t_minishell *ms)
{
	char	*cmd;

	cmd = 0;
	if (ms->n_pipe > 0)
	{
		//do something
	}
	else
	{
		cmd = add_whitespaces(ms->args[0]);
		exec_single_cmd(ms, cmd);
		free(ms->input);
	}
	get_exit_status(ms);
	free_program(ms, 0);
}
