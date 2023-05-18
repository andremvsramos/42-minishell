/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hexastr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:26:28 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_get_hexastr(unsigned long long nb, char *base)
{
	int		nb_length;
	char	*hexastr;

	nb_length = ft_getlength(nb, 16);
	hexastr = (char *)malloc(sizeof(char) * (nb_length + 1));
	if (!hexastr)
		return (0);
	hexastr[nb_length] = '\0';
	while (nb_length > 0)
	{
		hexastr[nb_length - 1] = base[nb % 16];
		nb /= 16;
		nb_length--;
	}
	return (hexastr);
}
