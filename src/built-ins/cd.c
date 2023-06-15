/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:42:56 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/15 10:04:14 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*get_home(t_minishell *ms, char *arg)
{
	char	*new;
	char	*temp;

	temp = get_env_info(&ms->env, "HOME");
	new = ft_strjoin(temp, arg + 1);
	return (new);
}

static void	execute_cd(t_minishell *ms, char *path)
{
	char	*old_pwd;
	char	*new_path;
	char	*temp;
	char	*new_pwd;

	/* if (path[0] == '~')
		new_path = get_home(ms, path);
	else if (path[0] == '-')
		new_path = ft_strdup(get_env_info(&ms->env, "OLDPWD"));
	else */
	new_path = ft_strdup(path);
	temp = getcwd(0, 0);
	old_pwd = ft_strjoin("OLDPWD=", temp);
	free(temp);
	update_info(ms->env, "OLDPWD", old_pwd);
	update_export(ms->xprt, "OLDPWD", old_pwd);
	chdir(new_path);
	free(new_path);
	temp = getcwd(0, 0);
	new_pwd = ft_strjoin("PWD=", temp);
	free(temp);
	update_info(ms->env, "PWD", new_pwd);
	update_export(ms->xprt, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
}

static void	check_errors(t_minishell *ms, char **cmd_args)
{
	struct stat		statbuf;

	if (cmd_args[1][0] == '~')
		cmd_args[1] = get_home(ms, cmd_args[1]);
	else if (ft_strlen(cmd_args[1]) == 1 && !ft_strncmp(cmd_args[1], "-", 1))
		cmd_args[1] = ft_strdup(get_env_info(&ms->env, "OLDPWD"));
	if (stat(cmd_args[1], &statbuf) == 0)
	{
		free_child(ms, cmd_args, 0);
		exit(0);
	}
	else if (cmd_args[1][0] == '-' && cmd_args[1][1])
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd_args[1], 2);
		ft_putstr_fd(": Invalid option\n", 2);
		free_child(ms, cmd_args, 0);
		exit (2);
	}
	else
		handle_error_cd(ms, cmd_args);
}

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
			execute_cd(ms, get_env_info(&ms->env, "HOME"));
		else if (cmd_args[1][0] == '~' && i == 2)
			execute_cd(ms, get_env_info(&ms->env, "HOME"));
		else if (cmd_args[1][0] == '-' && i == 2)
			execute_cd(ms, get_env_info(&ms->env, "OLDPWD"));
		else
			execute_cd(ms, cmd_args[1]);
		/* if (i == 1)
			execute_cd(ms, get_env_info(&ms->env, "HOME"));
		else
			execute_cd(ms, cmd_args[1]); */
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
		check_errors(ms, cmd_args);
}