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

/**
 * Retrieves the environment variables and stores them in a
 * export type table.
 *
 * @param env The environment variables as an array of strings.
 * @return A pointer to the head of the linked list containing the exported
 * variables.
 */
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

/**
 * Creates a new t_env structure and initializes it with the provided
 * information.
 *
 * @param info The information string containing the name and value of an
 * environment variable.
 * @return A pointer to the created t_env structure.
 */
t_env	*ft_create_export(char *info)
{
	t_env	*data;

	data = ft_calloc(1, sizeof(t_env));
	data->name = get_name(info);
	data->info = declare(info);
	return (data);
}

/**
 * Extracts the value portion from the information string of an
 * environment variable.
 *
 * @param info The information string containing the name and value
 * of an environment variable.
 * @return The extracted value portion of the environment variable.
 */
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
