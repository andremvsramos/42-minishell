/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:03:43 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/18 12:10:02 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct	s_minishell
{
	t_list	*env;
	t_list	*xprt;
	char	*prompt;
	char	*query;
	char	**fq;
}				t_minishell;


typedef struct	s_env
{
	char	*name;
	char	*info;
}				t_env;

//EXPORT
t_list	*get_export(char **env);
t_env	*ft_create_export(char *info);
char	*get_export_info(char *info);
char	*get_info(char *info);

//ENV VARIABLES
t_list	*init_env(char **env);
t_env	*ft_create_data(char *info);
char	*get_name(char *info);
char	**ft_envcpy(t_list *env);

//PROMPT
char	*get_prompt();

//CLEANUP
void	ft_free_lst(t_list *lst);

//PARSING
int		parse_query(t_minishell *ms);
int		check_valid_query(char *cmd, t_minishell *ms);

//BUILT-INS
int		check_unset_query(t_minishell *ms);
int		check_if_builtin(t_minishell *ms);
void	env_print(t_list *lst);
void	do_unset(t_list *lst, char *name);

#endif
