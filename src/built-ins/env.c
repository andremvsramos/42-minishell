/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:52:04 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/07 12:05:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_maxlen(char *s1, char *s2)
{
	int	i;
	int	j;

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
		printf("%s\n", ((t_env *)(temp->content))->info);
		temp = temp->next;
	}
}

void	print(int size, char **list)
{
	int	i;

	i = 0;
	while (i < size)
		printf("%s\n", list[i++]);
	free(list);
}

void	free_cpy(char *cpy1, char *cpy2)
{
	free(cpy1);
	free(cpy2);
}
