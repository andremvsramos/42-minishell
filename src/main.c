/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:03:14 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/25 15:45:54 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_exit = 0;

int	main(int ac, char **av, char **env)
{
	int			i;
	t_minishell	ms;

	(void)av;
	if (ac != 1)
		return (0);
	ms.env = init_env(env);
	ms.xprt = get_export(env);
	ms.prompt = get_prompt();
	while (1)
	{
		i = 0;
		signal_handling();
		i = read_input(&ms);
		if (!i)
			continue ;
		else if (i == -1)
			break ;
	}
	ft_free_lst(ms.env);
	ft_free_lst(ms.xprt);
	if (ms.input)
		free(ms.input);
	if (ms.prompt)
		free(ms.prompt);
	return (0);
}
