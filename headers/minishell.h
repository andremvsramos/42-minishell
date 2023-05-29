/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:03:43 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/29 11:14:34 by marvin           ###   ########.fr       */
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
# include <signal.h>

extern int	g_exit;

typedef struct s_minishell
{
	t_list	*env;
	t_list	*xprt;
	int		n_cmd;
	int		n_pipe;
	int		in_fd;
	int		out_fd;
	pid_t	*pid;
	bool	heredoc;
	char	*prompt;
	char	*input;
	char	**query;
	char	**paths;
}				t_minishell;

typedef struct s_env
{
	char	*name;
	char	*info;
}				t_env;

//INPUTS
int		read_input(t_minishell *ms);

//EXPORT
t_list	*get_export(char **env);
t_env	*ft_create_export(char *info);
char	*get_export_info(char *info);
char	*get_info(char *info);
int		ft_maxlen(char *s1, char *s2);

//ENV VARIABLES
t_list	*init_env(char **env);
t_env	*ft_create_data(char *info);
char	*get_name(char *info);
char	**ft_envcpy(t_list *env);

//EXECUTER
void	execute(t_minishell *ms);

//PROMPT
char	*get_prompt(void);

//SIGNALS
void	signal_handling(void);
void	handler(int signal);

//CLEANUP
void	ft_free_lst(t_list *lst);

//PARSING
int		parse_query(t_minishell *ms);
int		check_valid_query(char *cmd, t_minishell *ms);
int		count_quotes(char *input, char quote);

//BUILT-INS
int		check_unset_query(t_minishell *ms);
int		check_if_builtin(t_minishell *ms);
void	env_print(t_list *lst);
void	exp_print(t_list *lst);
void	do_unset(t_list *lst, char *name);
void    do_echo(t_minishell *ms);

//ECHO FUNCTIONS
int		handle_quotes(char *input);

//EXPANDER
int		check_expandable(t_minishell *ms);
char	**expander(t_minishell *ms);

//HEREDOC
void	do_heredoc(t_minishell *ms);

//UTILS
char	get_quote(char c, char quote);
char	*get_env_info(t_list **env, char *name);

//SPLITTER
int		ft_wordcounter(char *str, char c);
int		ft_wordlen(char *str, char c);
char	**splitter(char *s, char c);

//ERROR HANDLING
int	check_valid_input(char *input);
int	check_quotes(char *input);

#endif
