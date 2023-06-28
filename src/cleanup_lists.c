/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_lists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:44:05 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 12:24:21 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Frees the memory allocated for a linked list.
 *
 * @param lst  The linked list to free.
 */
void	ft_free_lst(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	temp = lst;
	while (temp)
	{
		next = temp->next;
		free(((t_env *)(temp->content))->name);
		free(((t_env *)(temp->content))->info);
		free(temp->content);
		free(temp);
		temp = next;
	}
}
