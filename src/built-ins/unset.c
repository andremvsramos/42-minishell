/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:36:55 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/18 17:42:11 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	do_unset(t_list *lst, char *name)
{
	t_list	*temp;
	t_list	*prev;
	char	*temp_name;

	temp = lst;
	prev = 0;
	while (temp)
	{
		temp_name = ((t_env *)(temp->content))->name;
		if (!ft_strncmp(temp_name, name, ft_strlen(name)
				&& ft_strlen(temp_name) == ft_strlen(name)))
		{
			if (prev)
				prev->next = temp->next;
			else
				lst = temp->next;
			free(((t_env *)(temp->content))->name);
			free(((t_env *)(temp->content))->info);
			free((t_env *)temp->content);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
