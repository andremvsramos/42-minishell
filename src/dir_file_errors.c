/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:08:27 by marvin            #+#    #+#             */
/*   Updated: 2023/06/26 11:08:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Handles the case when the command being executed is a directory instead
 * of an executable file.
 *
 * @param cmd_query  The command query that resulted in a directory.
 * @param ms         The minishell structure.
 */
void	is_a_directory(char **cmd_query, t_minishell *ms)
{
	ft_putstr_fd(cmd_query[0], STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	free_child(ms, cmd_query, 0);
	g_exit = 126;
	exit(g_exit);
}

/**
 * Handles the case when the command being executed does not have the necessary
 * permissions to be executed.
 *
 * @param cmd_query  The command query that resulted in a permission error.
 * @param ms         The minishell structure.
 */
void	permission_error(char **cmd_query, t_minishell *ms)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_query[0], STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	free_child(ms, cmd_query, 0);
	g_exit = 126;
	exit(g_exit);
}

/**
 * Handles the case when the file or directory specified in the command
 * does not exist.
 *
 * @param cmd_query  The command query that resulted in a file or directory
 *                   error.
 * @param ms         The minishell structure.
 */
void	file_error(char **cmd_query, t_minishell *ms)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_query[0], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	free_child(ms, cmd_query, 0);
	g_exit = 127;
	exit(g_exit);
}
