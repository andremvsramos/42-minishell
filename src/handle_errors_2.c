/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:00:08 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/13 11:16:42 by andvieir         ###   ########.fr       */
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
	if (input[*i] == input[*i + 1])
		(*i)++;
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
