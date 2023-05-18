/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:11:28 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/18 16:03:05 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_if_builtin(t_minishell *ms)
{
	if (check_valid_query("echo", ms)){}
		//DO ECHO
	else if (check_valid_query("cd", ms)){}
		//DO CD
	else if (check_valid_query("pwd", ms)){}
		//DO PWD
	else if (check_valid_query("unset", ms))
		check_unset_query(ms);
	else if (check_valid_query("env", ms))
		env_print(ms->env);
	else if (check_valid_query("export", ms))
		exp_print(ms->xprt);
	else if (check_valid_query("exit", ms))
		return (1);
	return (0);
}

int	check_valid_query(char *cmd, t_minishell *ms)
{
	if (ft_strlen(cmd) == ft_strlen(ms->query)
		&& !ft_strncmp(cmd, ms->query, ft_strlen(cmd)))
		return (1);
	return (0);
}

int	check_unset_query(t_minishell *ms)
{
	char	**split;

	if (!ft_strncmp("unset", ms->query, ft_strlen("unset")))
	{
		split = ft_split(ms->query, 32);
		if (!split[1])
			return (0);
		do_unset(ms->env, split[1]);
		do_unset(ms->xprt, split[1]);
		free(split);
		return (1);
	}
	return (0);
}

int	parse_query(t_minishell *ms)
{
	pid_t	pid;
	char	**clear_temp;

	clear_temp = ft_calloc(2, sizeof(char *));
	clear_temp[0] = ft_strdup(ms->query);
	clear_temp[1] = NULL;

	if (!ms->query)
		return (0);
	if (check_if_builtin(ms))
		return (1);
	else if (check_valid_query("clear", ms))
	{
		pid = fork();
		if (!pid)
			execve("/usr/bin/clear", clear_temp, ft_envcpy(ms->env));
	}
	return (0);
}
