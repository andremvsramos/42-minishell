/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:12:08 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 12:06:32 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Initializes the environment by creating a linked list of
 * environment variables.
 *
 * @param env An array of strings containing the environment variables.
 * @return A pointer to the head of the linked list representing the
 * environment.
 */
t_list	*init_env(char **env)
{
	int		i;
	t_list	*head;
	t_list	*temp;

	i = 0;
	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(ft_create_data(env[i])));
	temp = head;
	i++;
	while (env[i])
	{
		temp->next = ft_lstnew(ft_create_data(env[i]));
		temp = temp->next;
		i++;
	}
	return (head);
}

/**
 * Creates a t_env structure and fills it with data.
 *
 * @param info The string containing the environment variable information.
 * @return A pointer to the created t_env structure.
 */
t_env	*ft_create_data(char *info)
{
	t_env	*data;

	data = ft_calloc(1, sizeof(t_env));
	data->name = get_name(info);
	data->info = ft_strdup(info);
	return (data);
}

/**
 * Extracts the name portion of an environment variable from the info string.
 *
 * @param info The string containing the environment variable information.
 * @return A pointer to the extracted name string.
 */
char	*get_name(char *info)
{
	char	*name;
	int		i;

	i = 0;
	while (info[i] && info[i] != '=')
		i++;
	name = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(name, info, i + 1);
	return (name);
}

/**
 * Creates a copy of the environment variables stored in a linked list.
 * This is done in order to generate the program's own variables instead of
 * using the system variables.
 *
 * @param env The linked list containing the environment variables.
 * @return A double-pointer array of strings containing the copied
 * environment variables.
 */
char	**ft_envcpy(t_list *env)
{
	t_list	*temp;
	char	**copy;
	int		i;
	int		size;

	i = 0;
	size = ft_lstsize(env);
	copy = ft_calloc(size + 1, sizeof(char **));
	temp = env;
	while (temp)
	{
		copy[i++] = ft_strdup(((t_env *)(temp->content))->info);
		temp = temp->next;
	}
	return (copy);
}
