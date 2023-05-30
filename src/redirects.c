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

char	**handle_redirects(t_minishell *ms, char *input)
{
	char	**cmd_query;
	int		i;
	int		n_args;

	i = 0;
	n_args = ft_wordcounter(input, ' ');
	cmd_query = splitter(input, ' ');
	free(input);
	while (cmd_query[i])
	{
		if (!ft_strncmp(cmd_query[i], "<<", ft_strlen(cmd_query[i])))
			heredoc(cmd_query, ms, &i, &n_args);
		i++;
	}
	return (cmd_query);
}
