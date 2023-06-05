/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:11:28 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/05 10:12:37 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_if_builtin(t_minishell *ms, char **input)
{
	if (!ft_strncmp(input[0], "echo", ft_strlen("echo")))
		do_echo(ms, input);
	else if (check_strcmp("cd", input[0]))
	{
	}
	else if (check_strcmp("pwd", input[0]))
		pwd_print(ms, input);
	else if (check_strcmp("unset", input[0]))
		check_unset_query(ms, input[1]);
	else if (check_strcmp("env", input[0]))
		env_print(ms->env);
	else if (check_strcmp("export", input[0]))
		exp_print(ms->xprt);
	else if (check_strcmp("exit", input[0]))
	{
		free_child(ms, input, 0);
		return (1);
	}
	return (0);
}

int	check_unset_query(t_minishell *ms, char *input)
{
	/*char	**split;

	//printf("%s", ms->input);
	split = ft_split(ms->input, 32);
	printf("%s", split[1]);*/
	if (!input)
		return (0);
	do_unset(ms->env, input);
	do_unset(ms->xprt, input);
	//free(split);
	return (1);
}

void	parse_query(t_minishell *ms, char **cmd_query)
{
	char		**clear_temp;
	int			i;

	//ms->query = ft_split(ms->input, ' ');
	i = 1;
	while (cmd_query[i])
	{
		if (ft_strchr(cmd_query[i], '$'))
			cmd_query[i] = expander(cmd_query[i], ms);
		i++;
	}
	if (!cmd_query)
		return ;
	if (check_if_builtin(ms, cmd_query))
		return ;
	if (check_strcmp("clear", cmd_query[0]))
	{
		clear_temp = ft_calloc(2, sizeof(char *));
		clear_temp[0] = ft_strdup(cmd_query[0]);
		clear_temp[1] = NULL;
		execve("/usr/bin/clear", clear_temp, ft_envcpy(ms->env));
	}
}
