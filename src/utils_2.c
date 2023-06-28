/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:03:19 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/28 11:31:32 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Retrieves the exit status of the child processes spawned by the minishell.
 *
 * @param ms A pointer to the minishell structure.
 */
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

/**
 * Checks if the given command is a built-in command and executes
 * the corresponding function.
 *
 * This function is used in the parent process for built-in commands that
 * require modification of information in the main process. If these commands
 * were to run on child processes, they wouldn't have any effect.
 *
 * For example, if we try to execute the command "export var=info" on a child
 * process, the main environment wouldn't be updated or changed.
 *
 * @param ms         A pointer to the minishell structure.
 * @param cmd_query  An array of strings containing the command and its
 * arguments.
 */
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
	else if (check_strcmp("cd", cmd_query[0]))
		check_cd(ms, ms->query);
}

/**
 * Checks if a character is alphanumeric or underscore.
 *
 * @param c The character to check.
 *
 * @return Returns 1 if the character is alphanumeric or underscore,
 * 0 otherwise.
 */
int	ft_isalnum_extra(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

/**
 * Removes redirection symbols from the input string and returns
 * the resulting command query.
 *
 * @param input The input string containing redirection symbols.
 *
 * @return Returns an array of strings representing the command query
 * without redirection symbols.
 */
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

/**
 * Expands environment variables and removes quotes from command
 * query strings.
 *
 * @param cmd_query The array of strings representing the command query.
 * @param ms        A pointer to the minishell structure.
 */
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
