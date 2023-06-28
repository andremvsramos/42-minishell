/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:45:58 by marvin            #+#    #+#             */
/*   Updated: 2023/06/12 12:45:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Format the environment variable declaration for export.
 *
 * @param str  The environment variable declaration.
 * @return     The formatted string for export.
 */
char	*declare(char *str)
{
	int		i;
	char	*name;
	char	*info;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
	{
		name = ft_strjoin("declare -x ", str);
		info = ft_strjoin(name, "=\"\"");
		return (free(name), info);
	}
	name = ft_substr(str, 0, i);
	info = ft_strjoin(name, "=\"");
	free(name);
	name = ft_strjoin(info, str + i + 1);
	free(info);
	info = ft_strjoin(name, "\"");
	free(name);
	name = ft_strjoin("declare -x ", info);
	free(info);
	return (name);
}

/**
 * Update the environment variables in the minishell structure.
 *
 * @param ms    The minishell structure.
 * @param info  The string containing the environment variable information.
 */
void	update_env(t_minishell *ms, char *info)
{
	int		i;
	char	*name;

	i = 0;
	while (info[i] && info[i] != '=')
		i++;
	if (info[i] != '=')
	{
		name = ft_substr(info, 0, i);
		update_export(ms->xprt, name, info);
		free(name);
		return ;
	}
	name = ft_substr(info, 0, i);
	update_info(ms->env, name, info);
	update_export(ms->xprt, name, info);
	free(name);
}

/**
 * Function used to process the export command in the minishell.
 * It waits for the child process to complete and checks the exit status.
 * This function executes only when running a single command and there are
 * no errors.
 *
 * @param ms         The minishell structure.
 * @param cmd_query  The command query.
 */
void	check_export(t_minishell *ms, char **cmd_query)
{
	int	status;
	int	i;

	i = 0;
	while (cmd_query[i])
		i++;
	wait(&status);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	if (g_exit != 2)
	{
		if (i > 1)
		{
			i = 0;
			g_exit = 0;
			while (cmd_query[++i])
				if (check_val(cmd_query[i]))
					update_env(ms, cmd_query[i]);
		}
	}
}
