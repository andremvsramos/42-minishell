/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:03:43 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/31 12:41:14 by tsodre-p         ###   ########.fr       */
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

# define REDIRECT "><"

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
	char	**args;
	char	**paths;
}				t_minishell;

typedef struct s_env
{
	char	*name;
	char	*info;
}				t_env;

typedef struct s_expander
{
	int		index;
	int		len;
	int		offset;
	int		quote;
	t_list	*temp;
}				t_expander;

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
void	parse_query(t_minishell *ms, char **cmd_query);
int		count_quotes(char *input, char quote);

//EXECUTER
void	execute(t_minishell *ms);
void	exec_single_cmd(t_minishell *ms, char *cmd);

//REDIRECTS
char	**handle_redirects(t_minishell *ms, char *input);

//BUILT-INS
int		check_unset_query(t_minishell *ms);
int		check_if_builtin(t_minishell *ms, char **input);
void	env_print(t_list *lst);
void	exp_print(t_list *lst);
void	do_unset(t_list *lst, char *name);
void	do_echo(char **input);
void	pwd_print(char **input);

//ECHO FUNCTIONS
int		handle_quotes(char *input);

//EXPANDER
int		check_expandable(t_minishell *ms);
char	*expander(char *name, t_minishell *ms);

//HEREDOC
void	do_heredoc(t_minishell *ms, char *lim);
void	heredoc(char **cmd_query, t_minishell *ms, int *i, int *n_args);

//UTILS
char	get_quote(char c, char quote);
char	*get_env_info(t_list **env, char *name);
char	*add_whitespaces(char *str);
size_t	ft_cmdlen(char *str);
int		check_strcmp(char *s1, char *s2);

//SPLITTER
int		ft_wordcounter(char *str, char c);
int		ft_wordlen(char *str, char c);
char	**splitter(char *s, char c);

//ERROR HANDLING
int		check_valid_input(char *input);
int		check_quotes(char *input);

#endif
