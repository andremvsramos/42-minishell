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

/*void	shift_redirect(char **cmd_query, int *i, int *count)
{

}*/

static void	handle_append(char **cmd_query, t_minishell *ms, int *i, int *count)
{
	(void)count;
	ms->out_fd = open(cmd_query[*i + 1], O_RDWR | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR);
	if (!ms->out_fd)
	{
		ft_putstr_fd("Error creating file\n", STDERR_FILENO);
		free_child(ms, cmd_query, 1);
	}
}

static void	handle_out(char **cmd_query, t_minishell *ms, int *i, int *count)
{
	(void)count;
	ms->out_fd = open(cmd_query[*i + 1], O_RDWR | O_CREAT
			| O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if (!ms->out_fd)
	{
		ft_putstr_fd("Error creating file\n", STDERR_FILENO);
		free_child(ms, cmd_query, 1);
	}
}

static void	handle_in(char **cmd_query, t_minishell *ms, int *i, int *count)
{
	(void)count;
	ms->in_fd = open(cmd_query[*i + 1], O_RDONLY);
	if (!ms->in_fd)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_query[*i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_child(ms, cmd_query, 1);
	}
}

char	**handle_redirects(t_minishell *ms, char *input)
{
	char	**cmd_query;
	int		i;
	int		n_args;
	int		count;

	i = 0;
	ms->in_fd = STDIN_FILENO;
	ms->out_fd = STDOUT_FILENO;
	n_args = ft_wordcounter(input, ' ');
	cmd_query = splitter(input, ' ');
	free(input);
	while (cmd_query[i])
	{
		// <<, >>, <, >
		if (!ft_strncmp(cmd_query[i], "<", ft_strlen(cmd_query[i])))
			handle_in(cmd_query, ms, &i, &count);
		if (!ft_strncmp(cmd_query[i], ">", ft_strlen(cmd_query[i])))
			handle_out(cmd_query, ms, &i, &count);
		if (!ft_strncmp(cmd_query[i], ">>", ft_strlen(cmd_query[i])))
			handle_append(cmd_query, ms, &i, &count);
		if (!ft_strncmp(cmd_query[i], "<<", ft_strlen(cmd_query[i])))
			heredoc(cmd_query, ms, &i, &n_args);
		i++;
	}
	return (cmd_query);
}
