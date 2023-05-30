/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:40:49 by marvin            #+#    #+#             */
/*   Updated: 2023/05/29 10:40:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	get_quote(char c, char quote)
{
	if (ft_strrchr("\"\'", c) && !quote)
		return (c);
	else if (ft_strrchr("\"\'", c) && quote == c)
		return (0);
	return (quote);
}

char	*get_env_info(t_list **env, char *name)
{
	char	*info;
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		if (check_strcmp(((t_env *)(temp->content))->name, name))
		{
			info = ft_strchr(((t_env *)(temp->content))->info, '=');
			info++;
			return (info);
		}
		temp = temp->next;
	}
	return (NULL);
}

char	*add_whitespaces(char *str)
{
	char	*res;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	res = ft_calloc(ft_cmdlen(str) + 1, sizeof(char));
	while (str[i])
	{
		quote = get_quote(str[i], quote);
		if (!quote && ft_strchr(REDIRECT, str[i]))
		{
			res[j++] = ' ';
			res[j++] = str[i++];
			if (str[i] == str[i - 1])
				res[j++] = str[i++];
			res[j++] = ' ';
		}
		res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

size_t	ft_cmdlen(char *str)
{
	int	len;
	int	i;

	i = 0;
	len  = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_strchr(REDIRECT, str[i]))
		{
			len += 3;
			i++;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

int	check_strcmp(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2)
		&& !ft_strncmp(s1, s2, ft_strlen(s1)))
		return (1);
	return (0);
}
