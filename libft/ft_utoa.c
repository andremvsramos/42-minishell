/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:28:49 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static int	ft_length(unsigned long long n)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

char	*ft_utoa(unsigned long long n)
{
	char	*result;
	int		length;

	length = ft_length(n);
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (0);
	result[length] = '\0';
	if (n == 0)
		result[0] = '0';
	while (n != 0)
	{
		length--;
		result[length] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	return (result);
}
