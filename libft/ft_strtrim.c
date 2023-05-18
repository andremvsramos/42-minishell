/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:28:37 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	char			*strtrim;
	unsigned int	start;
	unsigned int	end;

	start = 0;
	if (!str)
		return (0);
	end = ft_strlen(str);
	while (str[start] && ft_strchr((char *)set, str[start]))
		start++;
	while (end > start && ft_strchr((char *)set, str[end - 1]))
		end--;
	strtrim = ft_substr(str, start, (end - start));
	return (strtrim);
}
