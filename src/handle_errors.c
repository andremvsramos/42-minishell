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

void	cmd_err(char *cmd, char **cmd_args, t_minishell *ms)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free_child(ms, cmd_args, 0);
	g_exit = 127;
	exit (g_exit);
}
