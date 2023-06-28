/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:27:17 by marvin            #+#    #+#             */
/*   Updated: 2023/05/30 14:27:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Shifts the elements in the cmd_query array to remove redirection symbols
 * and their corresponding arguments.
 *
 * @param cmd_query The command query array.
 * @param i         A pointer to the current index in the cmd_query array.
 * @param count     A pointer to the count of elements in the cmd_query array.
 */
void	shift_redirect(char **cmd_query, int *i, int *count)
{
	int	index;

	index = *i;
	while (index < *count - 2)
	{
		free(cmd_query[index]);
		cmd_query[index] = ft_strdup(cmd_query[index + 2]);
		index++;
	}
	if (*count - 2 <= 0)
	{
		free(cmd_query[0]);
		free(cmd_query[1]);
	}
	else
	{
		free(cmd_query[index]);
		free(cmd_query[index + 1]);
	}
	*count = *count - 2;
	cmd_query[index] = 0;
	*i = -1;
}

/**
 * Handles the append redirection by opening the file in append mode
 * and shifting the cmd_query array.
 *
 * @param cmd_query The command query array.
 * @param ms        The minishell structure.
 * @param i         A pointer to the current index in the cmd_query array.
 * @param count     A pointer to the count of elements in the cmd_query array.
 */
static void	handle_append(char **cmd_query, t_minishell *ms, int *i, int *count)
{
	ms->out_fd = open(cmd_query[*i + 1], O_RDWR | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR);
	if (ms->out_fd < 0)
	{
		ft_putstr_fd("Error creating file\n", STDERR_FILENO);
		free_child(ms, cmd_query, 1);
	}
	shift_redirect(cmd_query, i, count);
}

/**
 * Handles the output redirection by opening the file in write mode and
 * shifting the cmd_query array.
 *
 * @param cmd_query The command query array.
 * @param ms        The minishell structure.
 * @param i         A pointer to the current index in the cmd_query array.
 * @param count     A pointer to the count of elements in the cmd_query array.
 */
static void	handle_out(char **cmd_query, t_minishell *ms, int *i, int *count)
{
	ms->out_fd = open(cmd_query[*i + 1], O_RDWR | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR);
	if (ms->out_fd < 0)
	{
		ft_putstr_fd("Error creating file\n", STDERR_FILENO);
		free_child(ms, cmd_query, 1);
	}
	shift_redirect(cmd_query, i, count);
}

/**
 * Handles the input redirection by opening the file in read mode and
 * shifting the cmd_query array.
 *
 * @param cmd_query The command query array.
 * @param ms        The minishell structure.
 * @param i         A pointer to the current index in the cmd_query array.
 * @param count     A pointer to the count of elements in the cmd_query array.
 */
static void	handle_in(char **cmd_query, t_minishell *ms, int *i, int *count)
{
	ms->in_fd = open(cmd_query[*i + 1], O_RDONLY);
	if (ms->in_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_query[*i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_child(ms, cmd_query, 1);
	}
	shift_redirect(cmd_query, i, count);
}

/**
 * Handles the input/output redirections in the command query by
 * calling the corresponding functions.
 *
 * @param ms     The minishell structure.
 * @param input  The input string containing the command query.
 *
 * @return The updated command query array after handling the redirections.
 */
char	**handle_redirects(t_minishell *ms, char *input)
{
	char	**cmd_query;
	int		i;
	int		count;

	i = 0;
	ms->in_fd = STDIN_FILENO;
	ms->out_fd = STDOUT_FILENO;
	count = ft_wordcounter(input, ' ');
	cmd_query = splitter(input, ' ');
	free(input);
	while (cmd_query[i])
	{
		if (!ft_strncmp(cmd_query[i], "<", ft_strlen(cmd_query[i])))
			handle_in(cmd_query, ms, &i, &count);
		else if (!ft_strncmp(cmd_query[i], ">", ft_strlen(cmd_query[i])))
			handle_out(cmd_query, ms, &i, &count);
		else if (!ft_strncmp(cmd_query[i], ">>", ft_strlen(cmd_query[i])))
			handle_append(cmd_query, ms, &i, &count);
		else if (!ft_strncmp(cmd_query[i], "<<", ft_strlen(cmd_query[i])))
			heredoc(cmd_query, ms, &i, &count);
		i++;
	}
	return (cmd_query);
}
