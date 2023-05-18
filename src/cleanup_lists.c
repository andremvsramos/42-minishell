/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_lists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:44:05 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/17 12:46:45 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
