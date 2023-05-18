/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:03:14 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/18 17:30:26 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
		i = read_input(&ms);
		if (i)
			break ;
	}
	ft_free_lst(ms.env);
	ft_free_lst(ms.xprt);
	if (ms.query)
		free(ms.query);
	if (ms.prompt)
		free(ms.prompt);
	return (0);
}
