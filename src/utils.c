/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:40:49 by marvin            #+#    #+#             */
/*   Updated: 2023/05/29 10:40:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	get_quote(char c, char quote)
{
	if (ft_strrchr("\"\'", c) && !quote)
		return (c);
	else if (ft_strrchr("\"\'", c) && quote == c)
		return (0);
	return (quote);
}

char	*get_env_info(t_list **env, char *name)
{
	char	*info;
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		if ((ft_strlen(name) == ft_strlen(((t_env *)(temp->content))->name))
			&& !ft_strncmp(name, ((t_env *)(temp->content))->name,
			ft_strlen(((t_env *)(temp->content))->name)))
		{
			info = ft_strchr(((t_env *)(temp->content))->info, '=');
			info++;
			return (info);
		}
		temp = temp->next;
	}
	return (NULL);
}
