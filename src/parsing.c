/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:11:28 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 11:19:44 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Retrieves the full path of a command executable.
 *
 * @param cmd  The command name.
 * @param ms   Pointer to the minishell structure.
 * @param i    Index variable for string traversal.
 * @return     The full path of the command executable, or NULL if not found.
 */
char	*get_command(char *cmd, t_minishell *ms, int i)
{
	char	*temp;
	char	*command;

	if (!cmd)
		return (0);
	if (!get_env_info(&ms->env, "PATH"))
		return ("NO_PATH_AVAILABLE");
	if (!access(cmd, X_OK))
		return (cmd);
	while (ms->paths[i])
	{
		temp = ft_strdup(ms->paths[i]);
		command = ft_strjoin(temp, "/");
		free(temp);
		temp = ft_strdup(command);
		free(command);
		command = ft_strjoin(temp, cmd);
		if (!access(command, F_OK))
			return (command);
		free(temp);
		free(command);
		i++;
	}
	return (0);
}

/**
 * Checks if the command is a built-in command and executes it if it is.
 *
 * @param ms     Pointer to the minishell structure.
 * @param input  The command and its arguments as an array of strings.
 * @return       0 if the command is not a built-in command.
 */
int	check_if_builtin(t_minishell *ms, char **input)
{
	if (!ft_strncmp(input[0], "echo", ft_strlen("echo")))
		do_echo(ms, input);
	else if (check_strcmp("cd", input[0]))
		cd(ms, input);
	else if (check_strcmp("pwd", input[0]))
		pwd_print(ms, input);
	else if (check_strcmp("unset", input[0]))
		do_unset(ms, input);
	else if (check_strcmp("env", input[0]))
		env_print(ms, ms->env, input);
	else if (check_strcmp("export", input[0]))
		do_export(ms, input);
	else if (check_strcmp("exit", input[0]))
		do_exit(ms, input, 1);
	return (0);
}

/**
 * Parses and executes the command query.
 *
 * @param ms         Pointer to the minishell structure.
 * @param cmd_query  The command query as an array of strings.
 */
void	parse_query(t_minishell *ms, char **cmd_query)
{
	char	*command;

	if (!cmd_query[0])
		free_child(ms, cmd_query, 1);
	if (check_if_builtin(ms, cmd_query))
		return ;
	if (!check_files(cmd_query, ms))
		file_error(cmd_query, ms);
	command = get_command(cmd_query[0], ms, 0);
	if (!command)
		cmd_err(cmd_query[0], cmd_query, ms);
	else if (check_strcmp("NO_PATH_AVAILABLE", command))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_query[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_child(ms, cmd_query, 0);
		g_exit = 127;
		exit (g_exit);
	}
	execve(command, cmd_query, ft_envcpy(ms->env));
}
