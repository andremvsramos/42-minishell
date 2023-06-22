/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:00:08 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/22 09:55:26 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	error_operator(char *error, char *operator)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(operator, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}

int	error_token(char *error, char metachar, int dup)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putchar_fd(metachar, STDERR_FILENO);
	if (dup == 1)
		ft_putchar_fd(metachar, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}

int	unexpected_redirect(char *input, int *i)
{
	printf("%s\n", input);
	if (input[*i] == input[*i + 1])
		(*i)++;
	(*i)++;
	if (input[*i] == ' ')
		while (input[*i] && input[*i] == ' ')
			(*i)++;
	if (input[*i] == '|')
		return (error_token(UNTOKEN, '|', 0));
	else if (input[*i - 1] == '>' && input[*i] == '|')
		return (error_operator(NOSUPPORT, ">|"));
	else if (ft_strrchr(REDIRECT, input[*i]) && !input[*i])
		return (error_operator(UNTOKEN, "newline"));
	else if (ft_strrchr(REDIRECT, input[*i]) && input[*i] != input[*i + 1])
		return (error_token(UNTOKEN, input[*i], 0));
	else if (ft_strrchr(REDIRECT, input[*i]) && input[*i] == input[*i + 1])
		return (error_token(UNTOKEN, input[*i + 1], 1));
	return (0);
}

void	handle_error_cd(t_minishell *ms, char **cmd_args)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(cmd_args[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_child(ms, cmd_args, 0);
	exit (1);
}
