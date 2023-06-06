/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:03:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/05 14:40:21 by tsodre-p         ###   ########.fr       */
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

void	check_builtins(t_minishell *ms, char *cmd)
{
	if (!cmd)
		return ;
	if (check_strcmp("exit", cmd))
		check_exit(ms, cmd);
}

/*
char	**remove_redir(char *input)
{
	char	**cmd_args;
	int		i;
	int		count;

	i = 0;
	count = ft_wordcounter(input, ' ');
	cmd_args = splitter(input, ' ');
	while (cmd_args[i])
	{

	}
}
 */
