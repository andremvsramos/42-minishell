/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:52:04 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/18 17:22:08 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_maxlen(char *s1, char *s2)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (s1[i] != '=')
		i++;
	while (s2[j] != '=')
		j++;
	if (i > j)
		return (i);
	return (j);
}

void	env_print(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		{
			if (ft_strlen(((t_env *)(temp->content))->name)	+ 4 == ft_strlen(((t_env *)(temp->content))->info))
				printf("%s\n", ((t_env *)(temp->content))->info);
			temp = temp->next;
		}
	}
}

void	exp_print(t_list *lst)
{
	int		i;
	char	*cpy_i;
	char	*cpy_j;
	char	**copy;

	i = 0;
	copy = ft_envcpy(lst);
	while (i < ft_lstsize(lst) - 1)
	{
		if (ft_strncmp(copy[i], copy[i + 1], ft_maxlen(copy[i], copy[i + 1])) > 0)
		{
			cpy_i = ft_strdup(copy[i]);
			cpy_j = ft_strdup(copy[i + 1]);
			free(copy[i]);
			free(copy[i + 1]);
			copy[i] = ft_strdup(cpy_j);
			copy[i + 1] = ft_strdup(cpy_i);
			free(cpy_i);
			free(cpy_j);
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while (i < ft_lstsize(lst))
		printf("%s\n", copy[i++]);
	free(copy);
}
