/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:52:22 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 11:39:35 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * The function initializes the t_minishell structure with the provided input.
 *
 * @param ms    A pointer to the minishell structure.
 * @param input The input string containing the oommand query line.
 */
static void	ms_init(t_minishell *ms, char *input)
{
	ms->heredoc = false;
	ms->n_cmd = ft_wordcounter(input, '|');
	ms->n_pipe = ms->n_cmd - 1;
	ms->args = splitter(input, '|');
	ms->in_fd = STDIN_FILENO;
	ms->out_fd = STDOUT_FILENO;
	ms->pipe_fd = 0;
	ms->pid = ft_calloc(ms->n_cmd, sizeof(pid_t));
	ms->paths = ft_split(get_env_info(&ms->env, "PATH"), ':');
	ms->query = 0;
}

/**
 * Checks if quotes in the given input string are properly balanced.
 *
 * @param input A pointer to the input string to be checked.
 * @return Returns 0 if quotes are balanced or absent, 1 if there is
 * an unclosed quote.
 */
int	check_quotes(char *input)
{
	char	quote;

	quote = 0;
	while (*input && !quote)
	{
		if (ft_strrchr("\"\'", *input))
			quote = *input;
		input++;
	}
	while (*input && quote)
	{
		if (*input && *input == quote)
			quote = 0;
		input++;
	}
	if (*input)
		return (check_quotes(input));
	else if (!quote)
		return (0);
	else
		return (1);
}

/**
 * Reads input from the user, trims and validates it, and initializes
 * the t_minishell structure accordingly.
 *
 * @param ms A pointer to the t_minishell structure.
 * @return Returns 1 if the input is valid and initialized successfully,
 * 0 if the input is invalid, and -1 if there was an error reading input.
 */
int	read_input(t_minishell *ms)
{
	char	*trimmed;

	ms->prompt = get_prompt(ms, 0, 0);
	if (!ms->prompt)
		ms->prompt = ft_strdup("user> ");
	ms->input = readline(ms->prompt);
	free(ms->prompt);
	if (!ms->input)
		return (-1);
	if (ft_strlen(ms->input))
		add_history(ms->input);
	trimmed = ft_strtrim(ms->input, " ");
	free(ms->input);
	if (!check_valid_input(trimmed))
	{
		free(trimmed);
		g_exit = 2;
		return (0);
	}
	ms_init(ms, trimmed);
	free(trimmed);
	return (1);
}
