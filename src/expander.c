/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:49:39 by marvin            #+#    #+#             */
/*   Updated: 2023/05/26 13:49:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*expander(char	*name, t_minishell *ms)
{
	t_list	*temp;

	name = ft_strtrim(name, "\"\'");
	if ((name[0] == '$' && ft_strlen(name) == 1) || check_strcmp("$?", name))
		return (name);
	name = ft_strtrim(name, "$");
	temp = ms->env;
	while (temp)
	{
		if (check_strcmp(name, ((t_env *)(temp->content))->name))
		{
			free(name);
			name = ft_strdup(((t_env *)(temp->content))->info
					+ ft_strlen(((t_env *)(temp->content))->name) + 1);
			break ;
		}
		temp = temp->next;
	}
	if (!temp)
	{
		free(name);
		name = ft_strdup("");
	}
	return (name);
}
