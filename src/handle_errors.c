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

/**
 * Checks for unexpected tokens and redirects in the input string.
 *
 * @param input The input string to check.
 * @return 0 if no unexpected tokens or redirects are found, 1 otherwise.
 */
int	unexpected_tokens(char *input)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (input[++i])
	{
		quote = get_quote(input[i], quote);
		if (input[i] == '|' && input[i + 1] == ' ' && !quote)
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (input[i] && input[i] == ' ')
				return (error_token(UNTOKEN, '|', 0));
		}
		else if (ft_strrchr(REDIRECT, input[i]) && !quote)
			if (unexpected_redirect(input, &i))
				return (1);
	}
	return (0);
}

/**
 * Checks for unsupported operators and tokens in the input string.
 *
 * @param input The input string to check.
 * @return 0 if all operators and tokens are supported, 1 otherwise.
 */
int	check_supported_op(char *input)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (input[++i])
	{
		quote = get_quote(input[i], quote);
		if (i + 1 < (int)ft_strlen(input)
			&& input[i] == '|' && input[i + 1] == '|' && !quote)
			return (error_operator(NOSUPPORT, "||"));
		else if (ft_strrchr(NOHANDLE, input[i]) && !quote)
			return (error_token(NOSUPPORT, input[i], 0));
		else if (input[i] == '<' && input[i + 1] == '>' && !quote)
			return (error_operator(NOSUPPORT, "<>"));
		else if (i + 2 < (int)ft_strlen(input)
			&& input[i] == '<' && input[i + 1] == '<'
			&& input[i + 2] == '<' && !quote)
			return (error_operator(NOSUPPORT, "<<<"));
	}
	return (unexpected_tokens(input));
}

/**
 * Checks for invalid syntax in the input string.
 *
 * @param input The input string to check.
 * @return 0 if the syntax is valid, 1 otherwise.
 */
int	check_invalid_syntax(char *input)
{
	if (input[1] && input[0] == '|' && input[1] != '|')
		return (error_token(UNTOKEN, '|', 0));
	else if (input[1] && input[0] == '|' && input[1] == '|')
		return (error_token(UNTOKEN, '|', 1));
	if (input[ft_strlen(input) - 1] == '|')
	{
		ft_putstr_fd("minishell: no support for pipe prompt\n", STDERR_FILENO);
		return (1);
	}
	else if (ft_strrchr(REDIRECT, input[ft_strlen(input) - 1]))
		return (error_operator(UNTOKEN, "newline"));
	return (0);
}

/**
 * Checks if the input string is a valid command input.
 *
 * @param input The input string to check.
 * @return 1 if the input is valid, 0 otherwise.
 */
int	check_valid_input(char *input)
{
	if (!input || input[0] == '\0')
		return (0);
	if (check_quotes(input))
	{
		ft_putstr_fd("minishell: unclosed quotes\n", STDERR_FILENO);
		return (0);
	}
	if (check_supported_op(input))
		return (0);
	if (check_invalid_syntax(input))
		return (0);
	return (1);
}

/**
 * Prints an error message indicating that a command is not found.
 *
 * @param cmd The command that was not found.
 * @param cmd_args The arguments associated with the command.
 * @param ms The pointer to the minishell structure.
 */
void	cmd_err(char *cmd, char **cmd_args, t_minishell *ms)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free_child(ms, cmd_args, 0);
	g_exit = 127;
	exit (g_exit);
}
