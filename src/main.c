/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:03:14 by andvieir          #+#    #+#             */
/*   Updated: 2023/07/03 12:56:43 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * The use of a global variable like g_exit allows the exit status to be
 * accessed
 * and modified from different parts of the program, including signal handlers
 * or functions that handle command execution. It provides a way to communicate
 * the exit status between different components of the minishell program.
 */
int	g_exit = 0;

/**
 * Frees the memory allocated for the minishell structure.
 *
 * @param ms The minishell structure to free.
 */
void	free_all(t_minishell ms)
{
	if (ms.env)
		ft_free_lst(ms.env);
	if (ms.xprt)
		ft_free_lst(ms.xprt);
	if (ms.input)
		free(ms.input);
}

/**
 * Execution of the minishell program.
 *
 * @param ac  Number of arguments passed to the program.
 * @param av  Arguments passed to the program.
 * @param env The environment variables imported from the system environment.
 */
int	main(int ac, char **av, char **env)
{
	int			i;
	t_minishell	ms;

	(void)av;
	if (ac > 1)
		printf("minishell: wrong number of arguments\n");
	else
	{
		ms.env = init_env(env);
		ms.xprt = get_export(env);
		while (1)
		{
			i = 0;
			signal_handling();
			i = read_input(&ms);
			if (!i)
				continue ;
			else if (i == -1)
				break ;
			execute(&ms);
		}
		return (rl_clear_history(), free_all(ms),
			ft_putstr("exit\n"), 0);
	}
	return (0);
}
