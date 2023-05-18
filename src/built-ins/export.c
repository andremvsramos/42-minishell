/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:10:33 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/17 17:10:31 by andvieir         ###   ########.fr       */
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
	data->info = get_export_info(info);
	return (data);
}

char	*get_export_info(char *info)
{
	char	*exp_info;
	char	*temp;
	char	*name;

	exp_info = ft_strdup("declare -x ");
	name = get_name(info);
	temp = ft_strjoin(exp_info, name);
	free(name);
	free(exp_info);
	exp_info = ft_strjoin(temp, "=\"");
	free(temp);
	name = get_info(info);
	temp = ft_strjoin(exp_info, name);
	free(name);
	free(exp_info);
	exp_info = ft_strjoin(temp, "\"");
	free(temp);
	return (exp_info);
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
	//content = ft_strjoin("", info + i - j);
	return (content);
}
