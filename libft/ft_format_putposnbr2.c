/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putposnbr2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:26:16 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int	ft_print_posnbrw2(char *number, t_buffer *values, int len)
{
	int	count;

	count = 0;
	while ((values->width--) > len)
		count += write(1, " ", 1);
	while ((values->precision--) > (int)ft_strlen(number))
		count += write(1, "0", 1);
	return (count);
}
