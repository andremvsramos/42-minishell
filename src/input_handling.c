/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:52:22 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/15 12:12:21 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
