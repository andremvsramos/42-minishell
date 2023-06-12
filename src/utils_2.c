/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:03:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/12 14:08:39 by marvin           ###   ########.fr       */
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
	expand_args(cmd_query, ms);
	if (check_strcmp("exit", cmd_query[0]))
		check_exit(ms, ms->query);
	else if (check_strcmp("export", cmd_query[0]))
		check_export(ms, ms->query);
	else if (check_strcmp("unset", cmd_query[0]))
		check_unset(ms, ms->query);
}

int	ft_isalnum_extra(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
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

void	expand_args(char **cmd_query, t_minishell *ms)
{
	int	i;

	i = -1;
	while (cmd_query[++i])
		if (ft_strrchr(cmd_query[i], '$'))
			cmd_query[i] = expander(cmd_query[i], ms);
	i = -1;
	while (cmd_query[++i])
		if (ft_strrchr(cmd_query[i], '\'') || ft_strrchr(cmd_query[i], '\"'))
			cmd_query[i] = quote_remover(cmd_query[i]);
}
