/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:52:04 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/28 12:43:54 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * Display an error message for unsupported options or
 * arguments in the "env" command.
 *
 * @param ms         The minishell structure.
 * @param cmd_query  The command query.
 */
static void	env_print_error(t_minishell *ms, char **cmd_query)
{
	ft_putstr_fd("env: No options or arguments supported\n", STDERR_FILENO);
	free_child(ms, cmd_query, 0);
	g_exit = 1;
	exit (g_exit);
}

/**
 * Calculate the maximum length between two strings, considering the length
 * until the first '=' character.
 *
 * @param s1  The first string.
 * @param s2  The second string.
 * @return    The maximum length between the two strings.
 */
int	ft_maxlen(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	while (s2[j] && s2[j] != '=')
		j++;
	if (i > j)
		return (i);
	return (j);
}

/**
 * Print the environment variables stored in the linked list.
 *
 * @param ms          The t_minishell structure.
 * @param lst         The linked list of environment variables.
 * @param cmd_query   The command query.
 */
void	env_print(t_minishell *ms, t_list *lst, char **cmd_query)
{
	t_list	*temp;
	int		i;

	i = 0;
	while (cmd_query[i])
		i++;
	if (i > 1)
		env_print_error(ms, cmd_query);
	temp = lst;
	while (temp)
	{
		printf("%s\n", ((t_env *)(temp->content))->info);
		temp = temp->next;
	}
	free_child(ms, cmd_query, 0);
	g_exit = 0;
	exit(g_exit);
}

/**
 * Print an array of strings and free the memory.
 *
 * @param size  The size of the array.
 * @param list  The array of strings.
 */
void	print(int size, char **list)
{
	int	i;

	i = 0;
	while (i < size)
		printf("%s\n", list[i++]);
	ft_free_split(list);
}

/**
 * Free the memory allocated for two strings.
 *
 * @param cpy1  The first string to free.
 * @param cpy2  The second string to free.
 */
void	free_cpy(char *cpy1, char *cpy2)
{
	free(cpy1);
	free(cpy2);
}
