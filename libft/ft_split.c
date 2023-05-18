/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:28:04 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int	check_separator(const char a, char c)
{
	if (a == c)
		return (1);
	return (0);
}

int	count_strings(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && check_separator(str[i], c))
			i++;
		if (str[i])
			count++;
		while (str[i] && !check_separator(str[i], c))
			i++;
	}
	return (count);
}

int	ft_strlen_sep(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !check_separator(str[i], c))
		i++;
	return (i);
}

char	*ft_word(const char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	len_word = ft_strlen_sep(str, c);
	i = 0;
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *str, char c)
{
	char	**strings;
	int		i;
	int		wdcount;

	i = 0;
	if (!str)
		return (0);
	wdcount = count_strings(str, c);
	strings = (char **)malloc(sizeof(char *) * (wdcount + 1));
	while (*str)
	{
		while (*str && check_separator(*str, c))
			str++;
		if (*str)
		{
			strings[i] = ft_word(str, c);
			i++;
		}
		while (*str && !check_separator(*str, c))
			str++;
	}
	strings[i] = 0;
	return (strings);
}
/*
int	main(int ac, char **av)
{
	int		index;
	char	**split;
	(void)ac;
	split = ft_split(av[1], ' ');
	if (!split)
	{
		free(split);
		return (0);
	}
	index = 0;
	while (split[index])
	{
		printf("%s\n", split[index]);
		index++;
	}
	free(split);
	return (0);
}
*/
