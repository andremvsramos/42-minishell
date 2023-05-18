/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:28:41 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	if (!str)
		return (0);
	if (ft_strlen(str) <= start || !len)
		return (ft_strdup(""));
	if (ft_strlen(str) - start >= len)
		i = len + 1;
	else
		i = ft_strlen(str) - start + 1;
	substr = (char *)malloc(sizeof(char) * i);
	if (!substr)
		return (0);
	ft_strlcpy(substr, str + start, i);
	return (substr);
}
