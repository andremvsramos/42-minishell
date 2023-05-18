/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:03:14 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/18 12:34:28 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int ac, char **av, char **env)
{
	int	i;
	t_minishell	ms;

	i = 0;
	(void)av;
	if (ac != 1)
		return (0);
	ms.env = init_env(env);
	ms.xprt = get_export(env);
	ms.prompt = get_prompt();
	while (1)
	{
		ms.query = readline(ms.prompt);
		if (parse_query(&ms))
			break ;
		wait(0);
		free(ms.query);
	}
	ft_free_lst(ms.env);
	ft_free_lst(ms.xprt);
	if (ms.query)
		free(ms.query);
	if (ms.prompt)
		free(ms.prompt);
	return (0);
}
