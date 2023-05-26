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

int		check_expandable(t_minishell *ms)
{
	int	i;


	if (ms->query[0][0] == '<' && ms->query[0][1] == '<' && ms->heredoc == false)
	{
		ms->heredoc = true;
		return (0);
	}
	i = 0;
	while (ms->query[i])
	{
		if (ms->query[i][0] == '$')
			return (i);
		else
			i++;
	}
	return (0);
}

char	**expander(t_minishell *ms)
{
	int		index;
	int		len;
	t_list	*temp;

	//printf("THIS    %s\n", ms->query[0]);
	if (!ms->query)
		return (ms->query);
	index = check_expandable(ms);
	if (!index)
		return (ms->query);
	temp = ms->env;
	len = ft_strlen(ms->query[index] + 1);
	while (temp)
	{
		if (!ft_strncmp(ms->query[index] + 1, ((t_env *)(temp->content))->name,
			ft_strlen(((t_env *)(temp->content))->name))
			&& len == (int)ft_strlen(((t_env *)(temp->content))->name))
		{
			free(ms->query[index]);
			ms->query[index] = ft_strdup(((t_env *)(temp->content))->info + len + 1);
			break ;
		}
		temp = temp->next;
	}
	return (ms->query);
}
