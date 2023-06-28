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

/**
 * Expands the special variable `$?` to its value (the exit status) and adds
 * it to the result string.
 *
 * @param res  The result string to which the expanded value is added.
 * @param ms   The `t_minishell` structure containing relevant data.
 * @param i    The index of the current character being processed in the
 * input string.
 */
static void	expand_exit(char *res, t_minishell *ms, int *i)
{
	int		j;
	char	*value;

	value = ft_itoa(g_exit);
	j = -1;
	while (value[++j])
		res[ms->counter++] = value[j];
	free (value);
	*i += 1;
}

/**
 * Expands variables in the `arg` string and adds the expanded values
 * to the `res` string.
 *
 * @param arg  The input string containing variables to be expanded.
 * @param res  The result string to which the expanded values are added.
 * @param i    The index of the current character being processed in the
 * `arg` string.
 * @param ms   The `t_minishell` structure containing relevant data.
 */
static void	expand(char *arg, char *res, int *i, t_minishell *ms)
{
	char	*temp;
	char	*value;
	int		len;
	int		j;

	if (arg[*i + 1] != '?')
	{
		len = 0;
		while (ft_isalnum_extra(arg[*i + 1 + len]))
			len++;
		temp = ft_substr(arg, *i + 1, len);
		value = get_env_info(&ms->env, temp);
		if (!len)
			value = "$";
		free (temp);
		*i += len;
		if (value)
		{
			j = -1;
			while (value[++j])
				res[ms->counter++] = value[j];
		}
	}
	else
		expand_exit(res, ms, i);
}

/**
 * Support function for the function t_length.
 *
 * @param arg  The input string containing variables to be expanded.
 * @param i    The index of the current character being processed in the
 * `arg` string.
 * @param len  A pointer to the length variable that will be updated.
 * @param ms   The `t_minishell` structure containing relevant data.
 */
static void	t_length2(char *arg, int *i, int *len, t_minishell *ms)
{
	int		j;
	char	*temp;
	char	*value;

	j = 0;
	if (arg[*i + 1] != '?')
	{
		while (ft_isalnum_extra(arg[*i + 1 + j]))
			j++;
		temp = ft_substr(arg, *i + 1, j);
		value = get_env_info(&ms->env, temp);
		if (!j)
			value = "$";
		if (value)
			*len += ft_strlen(value);
		free(temp);
		*i += j;
	}
	else
	{
		temp = ft_itoa(g_exit);
		*len += ft_strlen(temp);
		free(temp);
		*i += 1;
	}
}

/**
 * Calculates the length of the expanded string without performing
 * the expansion.
 *
 * @param arg  The input string containing variables to be expanded.
 * @param ms   The `t_minishell` structure containing relevant data.
 * @return     The length of the expanded string.
 */
static int	t_length(char *arg, t_minishell *ms)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	len = 0;
	quote = 0;
	while (arg[++i])
	{
		quote = get_quote(arg[i], quote);
		if (arg[i] == '$' && quote != '\'')
			t_length2(arg, &i, &len, ms);
		else
			len++;
	}
	return (len);
}

/**
 * Expands variables in the input string and returns the expanded string.
 *
 * @param arg  The input string containing variables to be expanded.
 * @param ms   The `t_minishell` structure containing relevant data.
 * @return     The expanded string.
 */
char	*expander(char	*arg, t_minishell *ms)
{
	char	quote;
	char	*res;
	int		i;

	i = -1;
	ms->counter = 0;
	quote = 0;
	res = ft_calloc(t_length(arg, ms) + 1, sizeof(char));
	while (arg[++i])
	{
		quote = get_quote(arg[i], quote);
		if (arg[i] == '$' && quote != '\'')
			expand(arg, res, &i, ms);
		else
			res[ms->counter++] = arg[i];
	}
	res[ms->counter] = 0;
	free(arg);
	return (res);
}
