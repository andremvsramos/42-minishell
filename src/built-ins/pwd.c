/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:19:10 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/28 12:28:32 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Execute the pwd command and print the current working directory.
 *
 * @param ms     The minishell structure.
 * @param input  The input arguments for the pwd command.
 */
void	pwd_print(t_minishell *ms, char **input)
{
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
