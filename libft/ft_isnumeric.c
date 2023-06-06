/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:43:41 by marvin            #+#    #+#             */
/*   Updated: 2023/06/06 15:43:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (*str == '-')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		i++;
	}
	return (1);
}
