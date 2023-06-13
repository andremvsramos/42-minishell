/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:42:56 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/13 12:29:30 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	execute_cd(t_minishell *ms, char *path)
{
	char	*old_pwd;
	char	*new_path;
	char	*temp;
	char	*new_pwd;

	new_path = ft_strdup(path);
	temp = getcwd(0, 0);
	old_pwd = ft_strdup(temp);
	free(temp);
	update_info(ms->env, "OLDPWD", old_pwd);
	update_export(ms->xprt, "OLDPWD", old_pwd);
	chdir(new_path);
	free(new_path);
	temp = getcwd(0, 0);
	new_pwd = ft_strdup(temp);
	free(temp);
	update_info(ms->env, "PWD", new_pwd);
	update_export(ms->xprt, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
}

/*static void	check_errors(t_minishell *ms, char **cmd_args)
{
	struct stat		statbuf;

	if (cmd_args[1][0] == '~')
		cmd_args[1] =
}*/

void	check_cd(t_minishell *ms, char **cmd_args)
{
	int	status;
	int	i;

	i = 0;
	while (cmd_args[i])
		i++;
	wait(&status);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	if (g_exit == 0)
	{
		if (i == 1)
			execute_cd(ms, get_env_info(&ms->env , "HOME"));
			//i == 1 -> cd
			//i == 2 -> cd PATH
			/*if i is one change to home directory
			else change to the path on cmd_args[1]*/
		else if (cmd_args[1][0] == '~' && i == 1)
			execute_cd(ms, ft_strjoin("HOME=", get_env_info(&ms->env , "HOME")));
		else if (cmd_args[1][0] == '-' && i == 1)
			execute_cd(ms, ft_strjoin("HOME=", get_env_info(&ms->env , "OLDPWD")));
		else
			execute_cd(ms, cmd_args[1]);
	}
}

void	cd(t_minishell *ms, char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
		i++;
	if (i == 1)
	{
		free_child(ms, cmd_args, 0);
		g_exit = 0;
		exit (0);
	}
	if (i > 2)
	{
		ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
		free_child(ms, cmd_args, 0);
		g_exit = 1;
		exit (1);
	}
	else
		check_errors()
}
