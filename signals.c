/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:35:44 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/24 14:42:30 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	signal_handling(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
}
