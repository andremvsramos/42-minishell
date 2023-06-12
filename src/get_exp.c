/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:24:04 by marvin            #+#    #+#             */
/*   Updated: 2023/06/07 11:24:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_list	*get_export(char **env)
{
	int		i;
	t_list	*head;
	t_list	*temp;

	i = 0;
	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(ft_create_export(env[i])));
	temp = head;
	i++;
	while (env[i])
	{
		temp->next = ft_lstnew(ft_create_export(env[i]));
		temp = temp->next;
		i++;
	}
	return (head);
}

t_env	*ft_create_export(char *info)
{
	t_env	*data;

	data = ft_calloc(1, sizeof(t_env));
	data->name = get_name(info);
	data->info = declare(info);
	return (data);
}

char	*get_info(char *info)
{
	char	*content;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (info[i] != '=')
		i++;
	while (info[++i])
		j++;
	content = ft_substr(info, i - j, j);
	return (content);
}
