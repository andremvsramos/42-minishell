/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:03:43 by andvieir          #+#    #+#             */
/*   Updated: 2023/06/15 12:05:34 by tsodre-p         ###   ########.fr       */
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
# include <sys/stat.h>

# define REDIRECT "><"
# define NOHANDLE "&;(){}*\\"

# define UNTOKEN "minishell: syntax error near unexpected token '"
# define NOSUPPORT "minishell: no support for operator '"

extern int	g_exit;

typedef struct s_minishell
{
	t_list	*env;
	t_list	*xprt;
	int		n_cmd;
	int		n_pipe;
	int		in_fd;
	int		out_fd;
	int		counter;
	int		*pipe_fd;
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
char	*get_info(char *info);
int		ft_maxlen(char *s1, char *s2);
char	*declare(char *str);
void	export_error(t_minishell *ms, char **cmd_query);
int		check_val(char *str);
void	update_env(t_minishell *ms, char *info);
void	check_export(t_minishell *ms, char **cmd_query);

//ENV VARIABLES
t_list	*init_env(char **env);
t_env	*ft_create_data(char *info);
char	*get_name(char *info);
char	**ft_envcpy(t_list *env);

//EXECUTER
void	execute(t_minishell *ms);

//EXECUTER UTILS
void	redirect(int fd_in, int fd_out);

//PROMPT
//char	*get_prompt(void);
char	*get_prompt(t_minishell *ms, int i, int j);

//SIGNALS
void	signal_handling(void);
void	handler(int signal);
void	handler_sigint(int sig);
void	signal_default(void);

//CLEANUP
void	ft_free_lst(t_list *lst);
void	free_child(t_minishell *ms, char **cmd_query, int i);
void	free_program(t_minishell *ms, int i);

//PARSING
char	*get_command(char *cmd, t_minishell *ms);
void	parse_query(t_minishell *ms, char **cmd_query);

//EXECUTER
void	execute(t_minishell *ms);
void	exec_single_cmd(t_minishell *ms, char *cmd);
void	exec_multi_cmd(t_minishell *ms);
void	exec_cmd(t_minishell *ms, char *cmd, int i);
void	pipex(t_minishell *ms);
void	pipe_redirects(t_minishell *ms, int i);
void	close_pipex(t_minishell *ms);

//REDIRECTS
void	shift_redirect(char **cmd_query, int *i, int *count);
char	**handle_redirects(t_minishell *ms, char *input);

//BUILT-INS
void	check_builtins(t_minishell *ms, char **cmd_query);
int		check_if_builtin(t_minishell *ms, char **input);
void	do_export(t_minishell *ms, char **cmd_query);
void	env_print(t_minishell *ms, t_list *lst, char **cmd_query);
void	exp_print(t_list *lst);
void	print(int size, char **list);
void	free_cpy(char *cpy1, char *cpy2);
void	do_echo(t_minishell *ms, char **input);
void	pwd_print(t_minishell *ms, char **input);
void	do_exit(t_minishell *ms, char **cmd_query, int x);
void	do_unset(t_minishell *ms, char **cmd_query);
void	cd(t_minishell *ms, char **cmd_args);
void	check_cd(t_minishell *ms, char **cmd_args);

//EXIT
void	check_exit(t_minishell *ms, char **cmd_query);

//UNSET
void	check_unset(t_minishell *ms, char **cmd_query);

//QUOTES
char	*quote_remover(char *arg);

//EXPANDER
void	expand_args(char **cmd_query, t_minishell *ms);
int		check_expandable(t_minishell *ms);
char	*expander(char *name, t_minishell *ms);

//HEREDOC
void	do_heredoc(t_minishell *ms, char **input, char *lim);
void	heredoc(char **cmd_query, t_minishell *ms, int *i, int *n_args);
void	check_heredoc(t_minishell *ms, int i);

//UTILS
char	get_quote(char c, char quote);
char	*get_env_info(t_list **env, char *name);
char	*add_whitespaces(char *str);
char	**remove_redirects(char *input);
size_t	ft_cmdlen(char *str);
int		check_strcmp(char *s1, char *s2);
void	get_exit_status(t_minishell *ms);
int		ft_isalnum_extra(char c);
int		update_info(t_list *lst, char *name, char *new_info);
int		update_export(t_list *lst, char *name, char *new_info);

//SPLITTER
int		ft_wordcounter(char *str, char c);
int		ft_wordlen(char *str, char c);
char	**splitter(char *s, char c);

//ERROR HANDLING
int		check_valid_input(char *input);
int		check_quotes(char *input);
void	cmd_err(char *cmd, char **cmd_args, t_minishell *ms);
int		check_invalid_syntax(char *input);
int		check_supported_op(char *input);
int		unexpected_tokens(char *input);
int		error_operator(char *error, char *operator);
int		error_token(char *error, char metachar, int dup);
int		unexpected_redirect(char *input, int *i);
void	handle_error_cd(t_minishell *ms, char **cmd_args);

#endif
