/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:19:45 by fcaquard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/05 15:08:31 by npinheir         ###   ########.fr       */
=======
/*   Updated: 2022/03/05 13:47:01 by fcaquard         ###   ########.fr       */
>>>>>>> 457aecb1078473f5c28cb21c29bb7315e408256c
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

typedef struct s_token
{
	char		*token;
}	t_token;

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
}	t_redir;

typedef struct s_single_command
{
	char	*s_cmd;
	char	*exec;
	char	*instructions;
	size_t	ntokens;
	t_token	**tokens;
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

// apply redirections
int		apply_outredir(t_scmd *scmd);
void	create_redir_file_s(t_scmd *scmd);
void	create_redir_file_d(t_scmd *scmd);

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
int		remove_quotes(void);

// parsing
void	get_exec(void);
int		parse_cmd(void);
int		parse_param(t_scmd *s_cmd, size_t *start, size_t *i);
size_t	find_param_end(char *input, size_t position);
int		is_block_start(char c);
size_t	find_block_end(char *input, size_t position);
int		find_last_out(char *str);

// memory free
void	init_signals(void);
int		clear_all(void);
int		clear_exit(void);

// exec
void	exec(void);

// builtins
int		is_builtin(t_scmd *s_cmd);
void	buildins_pwd(t_scmd *scmd, int fd_out);
void	buildins_cd(t_scmd *scmd);
void	builtin_unset(t_scmd *scmd);
void	buildins_echo(t_scmd *scmd, int fd_out);
void	builtins_export(t_scmd *scmd);
void	builtins_env(void);
void	builtins_exit(void);

// utils
char	*remove_spaces(char *str);
int		is_in_quote(const char *s, int index);
char	*first_word(char *str);
int		ft_strcompare(const char *str, char *test);

// error handling
int		error_malloc(void);

// debug
void	print_cmd(size_t i);
void	print_redir(t_scmd	*s_cmd, size_t i);
void	print_envp(void);

#endif
