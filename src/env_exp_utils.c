/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:02:52 by marvin            #+#    #+#             */
/*   Updated: 2023/06/12 13:02:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	update_info(t_list *lst, char *name, char *new_info)
{
	t_list *temp;

	if (!lst)
		return (1);
	temp = lst;
	while (temp)
	{
		if (check_strcmp(name, ((t_env *)(temp->content))->name))
		{
			free(((t_env *)(temp->content))->info);
			((t_env *)(temp->content))->info = ft_strdup(new_info);
			return (0);
		}
		temp = temp->next;
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_create_data(new_info)));
	return (0);
}

int	update_export(t_list *lst, char *name, char *new_info)
{
	t_list *temp;

	if (!lst)
		return (1);
	temp = lst;
	while (temp)
	{
		if ((check_strcmp(name, ((t_env *)(temp->content))->name)))
		{
			free(((t_env *)(temp->content))->info);
			((t_env *)(temp->content))->info = declare(new_info);
			return (0);
		}
		temp = temp->next;
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_create_export(new_info)));
	return (0);
}
