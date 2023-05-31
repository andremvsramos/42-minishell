/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:19:10 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/05/31 15:12:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	pwd_print(t_minishell *ms, char **input)
{
	//nao suporta '-' >> g_exit = 2
	char	*path;
	int		count_args;

	count_args = 0;
	while (input[count_args])
		count_args++;
	if (count_args > 1)
	{
		if (input[1][0] == '-')
		{
			printf("%s\n", "pwd: does not support options");
			g_exit = 2;
			free_child(ms, input, 0);
			exit(g_exit);
		}
	}
	path = getcwd(0, 0);
	printf("%s\n", path);
	g_exit = 0;
	free(path);
	free_child(ms, input, 0);
	exit(0);
}
