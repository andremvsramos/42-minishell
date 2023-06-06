/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:03:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/06 16:19:01 by marvin           ###   ########.fr       */
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

void	check_builtins(t_minishell *ms, char **cmd_query)
{
	if (!cmd_query[0])
		return ;
	if (check_strcmp("exit", cmd_query[0]))
		check_exit(ms, ms->query);
}


char	**remove_redirects(char *input)
{
	char	**cmd_query;
	int		i;
	int		count;

	i = 0;
	count = ft_wordcounter(input, ' ');
	cmd_query = splitter(input, ' ');
	while (cmd_query[i])
	{
		if (!ft_strncmp(cmd_query[i], "<", ft_strlen(cmd_query[i])))
			shift_redirect(cmd_query, &i, &count);
		else if (!ft_strncmp(cmd_query[i], ">", ft_strlen(cmd_query[i])))
			shift_redirect(cmd_query, &i, &count);
		else if (!ft_strncmp(cmd_query[i], "<<", ft_strlen(cmd_query[i])))
			shift_redirect(cmd_query, &i, &count);
		else if (!ft_strncmp(cmd_query[i], ">>", ft_strlen(cmd_query[i])))
			shift_redirect(cmd_query, &i, &count);
		i++;
	}
	return (cmd_query);
}

