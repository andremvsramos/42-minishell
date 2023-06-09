/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:03:14 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/09 15:40:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_exit = 0;

void	free_all(t_minishell ms)
{
	if (ms.env)
		ft_free_lst(ms.env);
	if (ms.xprt)
		ft_free_lst(ms.xprt);
	if (ms.input)
		free(ms.input);
	if (ms.prompt)
		free(ms.prompt);
}

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
