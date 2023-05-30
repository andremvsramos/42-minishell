/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:53:50 by marvin            #+#    #+#             */
/*   Updated: 2023/05/26 14:53:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	hd_create_error()
{
	ft_putstr_fd("Error creating heredoc fil\n", STDERR_FILENO);
	exit (1);
}

void	do_heredoc(t_minishell *ms, char *lim)
{
	int		temp_file;
	char	*buffer;

	(void)ms;
	temp_file = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if (!temp_file)
		hd_create_error();
	while(1)
	{
		buffer = readline(">");
		/* if (!buffer)
		{ */
			/*DO ERROR*/
		/* } */
		if (!ft_strncmp(lim, buffer, ft_strlen(lim)))
			break ;
		if (ft_strrchr(buffer, '$'))
			buffer = expander(buffer, ms);
		ft_putendl_fd(buffer, temp_file);
		free(buffer);
	}
	free(buffer);
	close(temp_file);
}

void	heredoc(char **cmd_query, t_minishell *ms, int *i, int *n_args)
{
	(void)*n_args;
	do_heredoc(ms, cmd_query[*i + 1]);
	ms->in_fd = open(".heredoc", O_RDONLY);
	if (ms->in_fd < 0)
	{
		printf("ERRO");
		exit (1);
	}
	exit (1);
}
