/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:53:50 by marvin            #+#    #+#             */
/*   Updated: 2023/05/26 14:53:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Displays a warning message for an end-of-file error in a here-document.
 *
 * @param limiter The delimiter of the here-document.
 */
static void	eof_error(char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document", STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(limiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

/**
 * Checks if a here-document is present in the command arguments and updates
 * the heredoc flag.
 *
 * @param ms The minishell structure.
 * @param i The index of the current command in the arguments array.
 */
void	check_heredoc(t_minishell *ms, int i)
{
	int		j;
	char	*temp;
	char	**cmd_query;

	j = -1;
	temp = 0;
	cmd_query = 0;
	ms->heredoc = false;
	if (!i)
		return ;
	temp = add_whitespaces(ms->args[i - 1]);
	cmd_query = splitter(temp, ' ');
	while (cmd_query[++j])
		if (!ft_strncmp(cmd_query[j], "<<", ft_strlen(cmd_query[j])))
			ms->heredoc = true;
	free(temp);
	ft_free_split(cmd_query);
}

/**
 * Displays an error message for an error in creating a .heredoc file.
 *
 * @param ms The minishell structure.
 * @param input The command input as an array of strings.
 */
static void	hd_create_error(t_minishell *ms, char **input)
{
	ft_putstr_fd("minishell: Error creating .heredoc", STDERR_FILENO);
	free_child(ms, input, 1);
}

/**
 * Performs the handling of a here-document.
 *
 * @param ms The minishell structure.
 * @param input The command input as an array of strings.
 * @param lim The delimiter of the here-document.
 */
void	do_heredoc(t_minishell *ms, char **input, char *lim)
{
	int		temp_file;
	char	*buffer;

	temp_file = open(".heredoc", O_CREAT
			| O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if (temp_file < 0)
		hd_create_error(ms, input);
	while (1)
	{
		buffer = readline(">");
		if (!buffer)
		{
			eof_error(lim);
			break ;
		}
		if (!ft_strncmp(lim, buffer, ft_strlen(lim) + 1))
			break ;
		if (ft_strrchr(buffer, '$'))
			buffer = expander(buffer, ms);
		ft_putendl_fd(buffer, temp_file);
		free(buffer);
	}
	free(buffer);
	close(temp_file);
}

/**
 * Handles the here-document functionality for a command.
 *
 * @param cmd_query An array of strings representing the command and
 * its arguments.
 * @param ms The minishell structure.
 * @param i A pointer to the index of the current command in the
 * cmd_query array.
 * @param count A pointer to the number of commands in the cmd_query array.
 */
void	heredoc(char **cmd_query, t_minishell *ms, int *i, int *count)
{
	signal(SIGQUIT, SIG_IGN);
	do_heredoc(ms, cmd_query, cmd_query[*i + 1]);
	ms->in_fd = open(".heredoc", O_RDONLY);
	if (ms->in_fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(".heredoc", STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_child(ms, cmd_query, 1);
		exit(1);
	}
	shift_redirect(cmd_query, i, count);
}
