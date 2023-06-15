/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:52:56 by marvin            #+#    #+#             */
/*   Updated: 2023/06/07 11:52:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	close_pipex(t_minishell *ms)
{
	int	i;

	i = 0;
	while (i < ms->n_pipe * 2)
		close(ms->pipe_fd[i++]);
}

void	pipe_redirects(t_minishell *ms, int i)
{
	if (i == 0)
		redirect(ms->in_fd, ms->pipe_fd[1]);
	else if (i == ms->n_pipe)
		redirect(ms->pipe_fd[i * 2 - 2], ms->out_fd);
	else
		redirect(ms->pipe_fd[i * 2 - 2], ms->pipe_fd[i * 2 + 1]);
	close_pipex(ms);
}

void	redirect(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

void	pipex(t_minishell *ms)
{
	int	i;

	i = 0;
	while (i < ms->n_pipe)
	{
		if (pipe(ms->pipe_fd + (i * 2)) < 0)
		{
			ft_putstr_fd("minishell: pipe: error creating pipe\n",
				STDERR_FILENO);
			free_child(ms, NULL, 1);
		}
		i++;
	}
}
