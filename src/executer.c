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

/* void	exec_single_cmd(t_minishell *ms)
{
	ms->pid[0] = fork();
	if(!ms->pid[0])
	{

	}
} */

void	execute(t_minishell *ms)
{
	if (ms->n_pipe > 0)
		{}
	else
	{
		//exec_single_cmd(ms);
		parse_query(ms);
		free(ms->input);
		wait(0);
	}
}
