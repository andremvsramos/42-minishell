/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:19:22 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/26 08:46:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	get_env(char **user, char **temp)
{
	*user = getenv("USER");
	*temp = getenv("SESSION_MANAGER");
}

static char	*gd_utils(bool check, char *cwd, char *prompt, int length)
{
	char	*temp;

	if (check == false)
	{
		temp = ft_strdup(cwd);
		free(cwd);
		cwd = ft_strjoin(temp, "$ ");
		free(temp);
		temp = ft_strjoin(prompt, cwd);
		free(cwd);
		return (temp);
	}
	else
	{
		temp = ft_strdup(cwd + length);
		free(cwd);
		cwd = ft_strjoin("~", temp);
		free(temp);
		temp = ft_strjoin(cwd, "$ ");
		free(cwd);
		cwd = ft_strjoin(prompt, temp);
		free(temp);
		return (cwd);
	}
}

static char	*get_directory(t_minishell *ms, char *prompt)
{
	char	*cwd;
	size_t	length;

	cwd = getcwd(0, 0);
	length = ft_strlen(get_env_info(&ms->env, "HOME"));
	if (length > ft_strlen(cwd))
		cwd = gd_utils(false, cwd, prompt, length);
	else
		cwd = gd_utils(true, cwd, prompt, length);
	return (cwd);
}

char	*get_prompt(t_minishell *ms, int i, int j)
{
	char	*prompt;
	char	*user;
	char	*temp;

	get_env(&user, &temp);
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
	prompt = ft_strjoin(temp, ":");
	free(temp);
	temp = get_directory(ms, prompt);
	free(prompt);
	return (temp);
}
