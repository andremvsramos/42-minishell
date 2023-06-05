/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:31:22 by marvin            #+#    #+#             */
/*   Updated: 2023/05/29 10:31:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//int	check_support_op(char *input)

//int	check_invalid_syntax(char *input)

int	check_valid_input(char *input)
{
	if (!input || input[0] == '\0')
		return (0);
	if (check_quotes(input))
	{
		ft_putstr_fd("minishell: unclosed quotes\n", STDERR_FILENO);
		return (0);
	}
	/* if (check_support_op(input))
		return (0);
	if (check_invalid_syntax(input))
		return (0); */
	return (1);
}

void	cmd_err(char *cmd, char **cmd_args, t_minishell *ms)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free_child(ms, cmd_args, 0);
	g_exit = 127;
	exit (g_exit);
}
