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

/**
 * Updates an existing environment variable in a linked list.
 *
 * @param lst       The linked list containing the environment variables.
 * @param name      The name of the environment variable to update.
 * @param new_info  The new information for the environment variable.
 * @return 0 if the variable was successfully updated, 1 if the variable was
 * not found in the list.
 */
int	update_export(t_list *lst, char *name, char *new_info)
{
	t_list	*temp;

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
