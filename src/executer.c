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

void	exec_cmd(t_minishell *ms, char *cmd, int i)
{
	char	**cmd_query;

	if (ms->heredoc)
		wait (0);
	ms->pid[i] = fork();
	if (!ms->pid[i])
	{
		signal_default();
		cmd_query = handle_redirects(ms, cmd);
		pipe_redirects(ms, i);
		redirect(ms->in_fd, ms->out_fd);
		expand_args(cmd_query, ms);
		parse_query(ms, cmd_query);
	}
}

void	exec_multi_cmd(t_minishell *ms)
{
	char	*cmd;
	int		i;

	i = -1;
	ms->pipe_fd = ft_calloc(ms->n_pipe * 2, sizeof(int));
	if (!ms->pipe_fd)
	{
		ft_putstr_fd("minishell: failed allocating memory to ms->pipe_fd\n", STDERR_FILENO);
		free_child(ms, NULL, 1);
	}
	pipex(ms);
	while (ms->args[++i])
	{
		cmd = add_whitespaces(ms->args[i]);
		check_heredoc(ms, i);
		exec_cmd(ms, cmd, i);
		free(cmd);
	}
	close_pipex(ms);
}

void	exec_single_cmd(t_minishell *ms, char *cmd)
{
	char	**cmd_query;

	ms->pid[0] = fork();
	if (!ms->pid[0])
	{
		signal_default();
		cmd_query = handle_redirects(ms, cmd);
		redirect(ms->in_fd, ms->out_fd);
		expand_args(cmd_query, ms);
		parse_query(ms, cmd_query);
	}
}

void	execute(t_minishell *ms)
{
	char	*cmd;

	cmd = 0;
	if (ms->n_pipe > 0)
		exec_multi_cmd(ms);
	else
	{
		cmd = add_whitespaces(ms->args[0]);
		ms->query = remove_redirects(cmd);
		exec_single_cmd(ms, cmd);
		free(cmd);
		check_builtins(ms, ms->query);
		ft_free_split(ms->query);
	}
	get_exit_status(ms);
	free_program(ms, 0);
}
