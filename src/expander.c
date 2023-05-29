/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:49:39 by marvin            #+#    #+#             */
/*   Updated: 2023/05/26 13:49:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_expandable(t_minishell *ms)
{
	int		i;

	if (ms->query[0][0] == '<' && ms->query[0][1] == '<' && ms->heredoc == false)
	{
		ms->heredoc = true;
		return (0);
	}
	i = 0;
	while (ms->query[i])
	{
		if (ms->query[i][0] == '$')
			return (i);
		else if ((ms->query[i][0] == '\'' || ms->query[i][0] == '"') && ms->query[i][1] == '$')
			return (i);
		i++;
	}
	return (0);
}

static int	get_offset(char *name, int *quote, int (*f)(char *, char))
{
	*quote = f(name, '\'');
	if (!*quote)
		*quote = f(name, '"');
	if (!*quote)
		return (1);
	else
	{
		*quote = 1;
		return (2);
	}
	return (1);
}

static int	get_index(t_minishell *ms, int *index, int (*f)(t_minishell *))
{
	if (!ms->query)
		return (0);
	*index = f(ms);
	if (!*index)
		return (0);
	return (1);
}

char	**expander(t_minishell *ms)
{
	int		index;
	int		len;
	int		offset;
	int		quote;
	t_list	*temp;

	if (!get_index(ms, &index, check_expandable))
		return (ms->query);
	temp = ms->env;
	offset = get_offset(ms->query[index], &quote, count_quotes);
	len = ft_strlen(ms->query[index] + offset);
	while (temp)
	{
		if (!ft_strncmp(ms->query[index] + offset, ((t_env *)(temp->content))->name,
			ft_strlen(((t_env *)(temp->content))->name) - quote)
			&& len - quote == (int)ft_strlen(((t_env *)(temp->content))->name))
		{
			free(ms->query[index]);
			ms->query[index] = ft_strdup(((t_env *)(temp->content))->info + len + 1);
			break ;
		}
		temp = temp->next;
	}
	free(ms->query[index]);
	ms->query[index] = ft_strdup("");
	return (ms->query);
}
