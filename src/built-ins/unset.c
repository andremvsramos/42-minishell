/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:36:55 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 12:28:04 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Helper function to free memory for a single node in the 'unset' operation.
 *
 * @param temp  The node to free.
 */
static void	unset_free(t_list *temp)
{
	free(((t_env *)(temp->content))->name);
	free(((t_env *)(temp->content))->info);
	free((t_env *)temp->content);
}

/**
 * Helper function to handle unset error.
 *
 * @param ms         The minishell struct.
 * @param cmd_query  The command query.
 */
static void	unset_error(t_minishell *ms, char **cmd_query)
{
	ft_putstr_fd("minishell: unset: no options supported\n", STDERR_FILENO);
	free_child(ms, cmd_query, 0);
	g_exit = 2;
	exit (g_exit);
}

/**
 * Remove an environment variable from the list.
 *
 * @param lst  The list of environment variables.
 * @param name The name of the variable to unset.
 */
void	unset(t_list *lst, char *name)
{
	t_list	*temp;
	t_list	*prev;
	char	*temp_name;

	temp = lst;
	prev = 0;
	while (temp)
	{
		temp_name = ft_strdup(((t_env *)(temp->content))->name);
		if (check_strcmp(name, temp_name))
		{
			if (prev)
				prev->next = temp->next;
			else
				lst = temp->next;
			unset_free(temp);
			free(temp);
			free(temp_name);
			return ;
		}
		free(temp_name);
		prev = temp;
		temp = temp->next;
	}
}

/**
 * Function that unsets variables in the environment when only
 * performing a single command.
 *
 * @param ms         The minishell structure.
 * @param cmd_query  The command line arguments.
 */
void	check_unset(t_minishell *ms, char **cmd_query)
{
	int	status;
	int	i;

	i = 0;
	while (cmd_query[i])
		i++;
	wait(&status);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	if (!g_exit)
	{
		if (i > 1)
		{
			i = 0;
			while (cmd_query[++i])
			{
				unset(ms->env, cmd_query[i]);
				unset(ms->xprt, cmd_query[i]);
			}
		}
	}
}

/**
 * Execute the unset command and perform the necessary actions.
 *
 * @param ms         The minishell structure.
 * @param cmd_query  The command line arguments.
 */
void	do_unset(t_minishell *ms, char **cmd_query)
{
	int	i;

	i = 0;
	while (cmd_query[i])
		i++;
	if (i == 1)
	{
		free_child(ms, cmd_query, 1);
		g_exit = 0;
		exit (g_exit);
	}
	else if (i > 1)
	{
		if (cmd_query[1][0] == '-')
			unset_error(ms, cmd_query);
		i = 0;
		while (cmd_query[i])
		{
			free_child(ms, cmd_query, 0);
			g_exit = 0;
			exit (g_exit);
		}
	}
}
