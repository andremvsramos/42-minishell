/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:52:22 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/25 15:47:26 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	read_input(t_minishell *ms)
{
	ms->input = readline(ms->prompt);
	if (!ms->input)
	{
		printf("exit\n");
		return (-1);
	}
	ms->input = ft_strtrim(ms->input, " ");
	if (ft_strlen(ms->input))
		add_history(ms->input);
	if (parse_query(ms))
		return (1);
	free(ms->input);
	wait(0);
	return (0);
}
