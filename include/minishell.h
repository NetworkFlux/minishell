/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:19:45 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/03 17:18:09 by fcaquard         ###   ########.fr       */
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
#include <sys/ioctl.h>

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
	char	*f_cmd;
	size_t	nb_scmd;
	t_scmd	**s_cmd;
	char	**envp;
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

// env variables
void	env_variables(void);
int		find_env_variable(char *stack, char *needle);
char	*get_variable_value(char *str);

// remove quotes
int		remove_quotes(void);

// parsing
void	get_exec(void);
int		parse_cmd(void);
int		count_input(t_scmd *s_cmd, size_t start);
int		parse_param(t_scmd *s_cmd, size_t *start, size_t *i);
size_t	find_param_end(char *input, size_t position);
int		is_block_start(char c);
size_t	find_block_end(char *input, size_t position);
char	*tokenize(char *input, size_t start, size_t end);

// memory free
void	init_signals(void);
int		clear_all(void);

// exec
void	exec(void);

// builtins
int		is_builtin(t_scmd *s_cmd);
void	buildins_pwd(t_scmd *scmd);
void	buildins_cd(t_scmd *scmd);
void	builtin_unset(t_scmd *scmd);
void	buildins_echo(t_scmd *scmd);
void	builtins_export(t_scmd *scmd);

// utils
char	*remove_spaces(char *str);
int		is_in_quote(const char *s, int index);
char	*first_word(char *str);

// debug
void	print_cmd(size_t i);
void	print_redir(t_scmd	*s_cmd, size_t i);
void	debug_env(char *envv, char *str, char *result);
void	print_envp(void);

#endif
