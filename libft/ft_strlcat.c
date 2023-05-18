/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:28:17 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;
	size_t	a;

	i = 0;
	if (!size)
		return (ft_strlen((char *)src));
	destlen = ft_strlen((char *)dest);
	srclen = ft_strlen((char *)src);
	a = destlen;
	if (size <= destlen)
		return (srclen + size);
	while (src[i] && i < size - destlen - 1)
		dest[a++] = src[i++];
	dest[a] = '\0';
	return (destlen + srclen);
}
