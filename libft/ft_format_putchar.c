/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:26:02 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int	ft_format_putchar(t_buffer *values, char c)
{
	int	count;

	count = 0;
	if (values->minus == 1)
	{
		count += write(1, &c, 1);
		while (values->width > 1)
		{
			count += write(1, " ", 1);
			values->width--;
		}
	}
	else
	{
		while (values->width > 1)
		{
			count += write(1, " ", 1);
			values->width--;
		}
		count += write(1, &c, 1);
	}
	return (count);
}
