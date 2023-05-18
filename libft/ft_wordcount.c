/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:11:06 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:28:52 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int	ft_wordcount(const char *str, char c)
{
	int	i;
	int	wdcount;

	i = 0;
	wdcount = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			wdcount++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (wdcount);
}
