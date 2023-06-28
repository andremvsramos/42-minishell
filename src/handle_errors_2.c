/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:00:08 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 12:00:34 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Prints an error message indicating an invalid operator.
 *
 * @param error The error message to be displayed.
 * @param operator The invalid operator causing the error.
 * @return Returns 1.
 */
int	error_operator(char *error, char *operator)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(operator, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}

/**
 * Prints an error message indicating an unexpected token.
 *
 * @param error The error message to be displayed.
 * @param metachar The unexpected token causing the error.
 * @param dup Flag indicating whether the token should be duplicated in the
 * error message.
 * @return Returns 1.
 */
int	error_token(char *error, char metachar, int dup)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putchar_fd(metachar, STDERR_FILENO);
	if (dup == 1)
		ft_putchar_fd(metachar, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}

/**
 * Checks for unexpected redirect tokens and raises corresponding errors.
 *
 * @param input The input string.
 * @param i Pointer to the current position in the input string.
 * @return Returns 1 if an error occurs, 0 otherwise.
 */
int	unexpected_redirect(char *input, int *i)
{
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

/**
 * Handles the error case for the `cd` command.
 *
 * @param ms Pointer to the `t_minishell` struct.
 * @param cmd_args The command arguments.
 */
void	handle_error_cd(t_minishell *ms, char **cmd_args)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(cmd_args[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_child(ms, cmd_args, 0);
	exit (1);
}
