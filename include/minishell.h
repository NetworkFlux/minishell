/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.42.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:19:45 by fcaquard          #+#    #+#             */
/*   Updated: 2022/04/01 16:20:47 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <errno.h>
// # include <termios.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	char			*line;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_redirection
{
	size_t		out;
	size_t		outout;
	size_t		in;
	size_t		inin;
	char		**out_args;
	char		**outout_args;
	char		**in_args;
	char		**inin_args;
	int			last_out;
	int			last_in;
}	t_redir;

typedef struct s_single_command
{
	pid_t	pid;
	size_t	index;
	char	*s_cmd;
	char	*instructions;
	size_t	ntokens;
	char	**tokens;
	t_redir	*redir;
}	t_scmd;

typedef struct s_full_command
{
	char			*f_cmd;
	size_t			nb_scmd;
	t_scmd			**s_cmd;
	struct s_env	*envp;
	char			**env;
	int				exitcode;
	char			*exec_path;
	int				active_heredoc;
}	t_fcmd;

// GLOBAL
t_fcmd	*g_fcmd;

// take_input
char	*take_input(void);
int		is_input_incomplete(char *input);

// init
void	init_global(char **envp);
int		init_full_cmd(char *cmd);
t_redir	*init_redir(void);

// parse redir
int		parse_redir(void);
int		nb_redir(char *str, char c);
int		nb_dredir(char *str, char c);
void	fill_redir(t_scmd *s_cmd);
void	add_redir_arg(t_scmd *s_cmd, unsigned int i, int j, char c);
void	add_dredir_arg(t_scmd *s_cmd, unsigned int i, int j, char c);
int		redir_files_ok(t_scmd *scmd);
int		find_last_in(char *str);
int		find_last_out(char *str);

// variables
void	env_variables(void);
size_t	end_var(char *str, size_t i, size_t j);
char	*exit_code(char	*str, size_t i, size_t j);
char	*replace_var(char *str, char *env, size_t start, size_t end);
char	*get_env(char *str, size_t start, size_t end);

// environment
size_t	env_len(t_env *env);
t_env	*create_env(char	**envp);
t_env	*env_first(t_env *env);
t_env	*env_last(t_env *env);
t_env	*find_env(t_env *env, char *str);
int		add_env(t_env *env, char *name, char *value, char *line);
t_env	*remove_env(t_env *env);
char	**env_listtoarray(t_env *env, size_t len, size_t i);
int		insert_update_env(char *name, char *value);
char	*strrebuild(char *src1, char *src2, char *src3);

// apply redirections
int		apply_outredir(t_scmd *scmd);
void	create_redir_file_s(t_scmd *scmd);
void	create_redir_file_d(t_scmd *scmd);
char	**apply_inredir(t_scmd *scmd);
char	**apply_heredoc(t_scmd *scmd);
char	**get_heredoc(t_scmd *scmd);

// parsing
int		parse_cmd(void);
char	*parse_param(char *str, size_t *start);
size_t	find_param_end(char *input, size_t position);
int		is_block_start(char c);
size_t	find_block_end(char *input, size_t position);

// exec
void	__exec_full(size_t index, char **args, int piperead);
char	*find_path(t_scmd *scmd);

// pipeline
void	execute(t_scmd *s_cmd);
int		pipeline(t_scmd *scmd, void (foutput)(t_scmd *scmd), int readpipe);

// builtins
void	buildins_cd(t_scmd *scmd);
void	builtin_unset(t_scmd *scmd);
void	builtins_exit(t_scmd *scmd);
int		buildins_pwd(t_scmd *scmd, int readpipe);
int		buildins_echo(t_scmd *scmd, int readpipe);
int		builtins_export(t_scmd *scmd, int readpipe);
int		builtins_env(t_scmd *scmd, int readpipe);
int		route_builtins(t_scmd *scmd, size_t i, int readpipe);
int		find_builtin(t_scmd *s_cmd);

// memory free
void	init_signals(void);
int		clear_all(void);
void	clear_exit(int n);
int		kill_child(void);
int		clear_array(char **array, size_t len);

// realloc
char	**ft_realloc(char **tab, char *str);
char	*ft_copy(char *str);

// utils
char	*remove_spaces(char *str);
int		is_in_quote(const char *s, int index);
char	*first_word(char *str);
int		export_args(char *str);

// error handling
int		error_malloc(int n);
void	perr(int code, char *str);

// useful functions
int		ft_strisalpha(char *str);
size_t	find_char(char *str, char c);
char	*fillstr(size_t start, size_t end, const char *src);
char	**split_once(char *str, char c);
char	*ft_strcopy(char *dest, char *src, size_t index_dest);
int		ft_strcompare(const char *str, char *test);
size_t	ft_arrlen(char **arr);
char	*remove_quotes(char *input);
void	rl_replace_line(const char *text, int clear_undo);

// debug
void	print_cmd(size_t i);
void	print_redir(t_scmd	*s_cmd, size_t i);
void	print_tokens(t_scmd *scmd);
void	print_env_array(char **envp);
void	print_env_list(void);
void	print_array(char **array, char *str);

#endif
