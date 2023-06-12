/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:42:56 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/12 17:53:36 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
			//update_env(ms, get_name("HOME"));
			//i == 1 -> cd
			//i == 2 -> cd PATH
			/*if i is one change to home directory
			else change to the path on cmd_args[1]*/
	}
}
void	execute_cd(t_minishell *ms, char **cmd_args)
{

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
}
