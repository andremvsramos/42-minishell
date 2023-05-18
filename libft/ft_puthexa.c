/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:27:51 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int	ft_puthexa(unsigned long nb, char c)
{
	int		count;
	char	*base;

	count = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	if (nb < 16)
	{
		count += ft_putchar(base[nb]);
	}
	if (nb >= 16)
	{
		count += ft_puthexa(nb / 16, c);
		count += ft_puthexa(nb % 16, c);
	}
	return (count);
}
