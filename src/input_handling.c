/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:52:22 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/24 16:49:24 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	read_input(t_minishell *ms)
{
	ms->query = readline(ms->prompt);
	if (!ms->query)
	{
		printf("exit\n");
		return (-1);
	}
	ms->query = ft_strtrim(ms->query, " ");
	if (ft_strlen(ms->query))
		add_history(ms->query);
	if (parse_query(ms))
		return (1);
	free(ms->query);
	wait(0);
	return (0);
}
