/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlength.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:26:30 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int	ft_getlength(unsigned long long n, int base)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		length++;
		n /= base;
	}
	return (length);
}
