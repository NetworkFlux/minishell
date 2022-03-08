/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:19:45 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/08 15:04:16 by npinheir         ###   ########.fr       */
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

typedef	struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

// typedef struct s_token
// {
// 	char		*token;
// }	t_token;

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
	char	*s_cmd;
	char	*instructions;
	size_t	ntokens;
	char	**tokens;
	t_redir	*redir;
	pid_t	child_id;
}	t_scmd;

typedef struct s_full_command
{
	char			*f_cmd;
	size_t			nb_scmd;
	t_scmd			**s_cmd;
	struct s_env	*envp;
}	t_fcmd;

// GLOBAL
t_fcmd	*g_fcmd;

// take_input
char	*take_input(void);
int		is_input_incomplete(char *input);

// init
int		init_full_cmd(char *cmd);
t_redir	*init_redir(void);

// parse redir
int		parse_redir(void);
int		nb_redir(char *str, char c);
int		nb_dredir(char *str, char c);
void	fill_redir(t_scmd *s_cmd);
void	fill_s(t_scmd *s_cmd, char c);
void	fill_d(t_scmd *s_cmd, char c);
void	add_redir_arg(t_scmd *s_cmd, unsigned int i, int j, char c);
void	add_dredir_arg(t_scmd *s_cmd, unsigned int i, int j, char c);
int		redir_files_ok(t_scmd *scmd);
int		find_last_in(char *str);
int		find_last_out(char *str);

// apply redirections
int		apply_outredir(t_scmd *scmd);
void	create_redir_file_s(t_scmd *scmd);
void	create_redir_file_d(t_scmd *scmd);
char	**apply_inredir(t_scmd *scmd);
char	**get_fdin_data(t_scmd *scmd, int fd);
char	**apply_heredoc(t_scmd *scmd);

// env variables
void	env_variables(void);
t_env	*create_env(char	**envp);
char	**split_first_occurence(char *str, unsigned char c);
t_env	*env_first(t_env *env);
t_env	*env_last(t_env *env);
t_env 	*find_env(t_env *env, char *str);
t_env	*add_env(t_env *env, char *name, char *value);
t_env	*remove_env(t_env *env);

// remove quotes
char	*remove_quotes(char *input);

// parsing
// void	get_exec(void);
int		parse_cmd(void);
char	*parse_param(char *str, size_t *start);
size_t	find_param_end(char *input, size_t position);
int		is_block_start(char c);
size_t	find_block_end(char *input, size_t position);
int		find_last_out(char *str);

// memory free
void	init_signals(void);
int		clear_all(void);
int		clear_exit(void);
void	clear_env(void);

// exec
void	route_exec(char **envp);
void	exec(t_scmd *scmd, char **envp);

// builtins
void	buildins_pwd(t_scmd *scmd, int fd_out);
void	buildins_cd(t_scmd *scmd);
void	builtin_unset(t_scmd *scmd);
void	buildins_echo(t_scmd *scmd, int fd_out);
int		is_option_ok(char *str);
void	builtins_export(t_scmd *scmd);
void	builtins_env(t_scmd *scmd, int fd_out);
void	builtins_exit(void);

void	buildins_cat(t_scmd *scmd, int fd_out, char **fd_in);


// utils
char	*remove_spaces(char *str);
int		is_in_quote(const char *s, int index);
char	*first_word(char *str);
int		ft_strcompare(const char *str, char *test);
size_t	charsslen(int fd);
char	**realloc_heredoc(char **tab, size_t res_len, char *input);

// error handling
int		error_malloc(void);

// debug
void	print_cmd(size_t i);
void	print_redir(t_scmd	*s_cmd, size_t i);
void	print_envp(void);
void	print_tokens(t_scmd *scmd);

#endif
