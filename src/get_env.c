/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:12:08 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/17 15:49:50 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

t_env	*ft_create_data(char *info)
{
	t_env	*data;

	data = ft_calloc(1, sizeof(t_env));
	data->name = get_name(info);
	data->info = ft_strdup(info);
	return (data);
}

char	*get_name(char *info)
{
	char	*name;
	int		i;

	i = 0;
	while (info[i] != '=')
		i++;
	name = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(name, info, i + 1);
	return (name);
}

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
