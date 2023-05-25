/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:52:04 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/25 16:02:11 by andvieir         ###   ########.fr       */
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
		{
			printf("%s\n", ((t_env *)(temp->content))->info);
			temp = temp->next;
		}
	}
}

static void	print(int size, char **list)
{
	int	i;

	i = 0;
	while (i < size)
		printf("%s\n", list[i++]);
	free(list);
}

static void	free_cpy(char *cpy1, char *cpy2)
{
	free(cpy1);
	free(cpy2);
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
		if (ft_strncmp(copy[i], copy[i + 1],
				ft_maxlen(copy[i], copy[i + 1])) > 0)
		{
			cpy_i = ft_strdup(copy[i]);
			cpy_j = ft_strdup(copy[i + 1]);
			free_cpy(copy[i], copy[i + 1]);
			copy[i] = ft_strdup(cpy_j);
			copy[i + 1] = ft_strdup(cpy_i);
			free_cpy(cpy_i, cpy_j);
			i = 0;
		}
		else
			i++;
	}
	print(ft_lstsize(lst), copy);
}
