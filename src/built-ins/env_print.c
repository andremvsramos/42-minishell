/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:52:04 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/18 12:41:52 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* static int	ft_maxlen(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	return (ft_strlen(s2));
} */

void	env_print(t_list *lst)
{
	t_list	*temp;
	//char	*info;
	/* int		i;
	int		j; */
	/* char	*name_cpy;
	char	**copy; */

	temp = lst;
	/* if (ft_strncmp("declare", ((t_env *)(temp->content))->info,
			ft_strlen("declare")))
	{ */
		while (temp)
		{
			{
				/* info = ft_strdup(((t_env *)(temp->content))->info);
				if (info &&ft_strncmp("declare", info, 7)) */
				printf("%s\n", ((t_env *)(temp->content))->info);
				temp = temp->next;
				//free(info);
			}
		}
	/* }
	else
	{
		i = 0;
		copy = ft_envcpy(lst);
		while (copy[i])
		{
			printf("COPY[%d] >> %s\n", i, copy[i]);
			sleep(2);
			j = i + 1;
			while (copy[j])
			{
				if (ft_strncmp(copy[i], copy[j], ft_maxlen(copy[i], copy[j])))
				{
					name_cpy = ft_strdup(copy[i]);
					ft_strlcpy(copy[i], copy[j], ft_strlen(copy[j]));
					ft_strlcpy(copy[j], name_cpy, ft_strlen(name_cpy));
				}
				j++;
			}
			i++;
		}

		i = 0;
		while (copy[i])
			printf("%s\n", copy[i++]);
	} */
}

