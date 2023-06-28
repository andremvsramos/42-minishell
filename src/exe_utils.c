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

/**
 * Checks if the command in cmd_query corresponds to a valid executable file.
 *
 * @param cmd_query The command to be checked, represented as an array
 * of strings.
 * @param ms The t_minishell structure containing relevant data.
 * @return 1 if the command corresponds to a valid executable file,
 * 0 otherwise.
 */
int	check_files(char **cmd_query, t_minishell *ms)
{
	struct stat	statbuf;

	if (ft_strrchr(cmd_query[0], '/') || !ms->paths)
	{
		if (stat(cmd_query[0], &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
				is_a_directory(cmd_query, ms);
			else if (!(statbuf.st_mode & S_IXUSR))
				permission_error(cmd_query, ms);
			return (1);
		}
		else
			return (0);
	}
	return (1);
}

/**
 * Closes the file descriptors associated with the pipes used in
 * piped commands.
 *
 * @param ms The t_minishell structure containing relevant data.
 */
void	close_pipex(t_minishell *ms)
{
	int	i;

	i = 0;
	while (i < ms->n_pipe * 2)
		close(ms->pipe_fd[i++]);
}

/**
 * Redirects input and output for commands involved in piping.
 *
 * @param ms The t_minishell structure containing relevant data.
 * @param i The index of the current command in the pipeline.
 */
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

/**
 * Redirects file descriptors to standard input and standard output.
 *
 * @param fd_in The file descriptor to redirect to standard input.
 * @param fd_out The file descriptor to redirect to standard output.
 */
void	redirect(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

/**
 * Creates multiple pipes for inter-process communication.
 *
 * @param ms The minishell structure.
 */
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
