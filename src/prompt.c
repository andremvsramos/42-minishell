/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:19:22 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/18 12:48:14 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_prompt()
{
	char	*prompt;
	char	*user;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	user = getenv("USER");
	temp = getenv("SESSION_MANAGER");
	if (!user || !temp)
		return (NULL);
	prompt = ft_strdup(user);
	while (temp[i] != '/')
		i++;
	user = ft_strjoin(prompt, "@");
	free(prompt);
	while (temp[++i] != '.')
		j++;
	prompt = ft_substr(temp, i - j, j);
	temp = ft_strjoin(user, prompt);
	free(prompt);
	free(user);
	prompt = ft_strjoin(temp, ">");
	free(temp);
	return (prompt);
}
