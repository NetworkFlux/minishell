/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:19:45 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/21 18:51:14 by fcaquard         ###   ########.fr       */
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

typedef	struct	s_env
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
	pid_t			child_id;
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
// char	**get_fdin_data(t_scmd *scmd);		// doesn't exist
char	**apply_heredoc(t_scmd *scmd);
char	**get_heredoc(t_scmd *scmd);

// env variables
void	env_variables(void);
t_env	*create_env(char	**envp);
// char	**split_first_occurence(char *str, unsigned char c);	// doesn't exist
t_env	*env_first(t_env *env);
t_env	*env_last(t_env *env);
t_env 	*find_env(t_env *env, char *str);
t_env	*add_env(t_env *env, char *name, char *value, char *line);
t_env	*remove_env(t_env *env);
char	**env_listtoarray(t_env *env);
// void	print_envp(void);					// doesn't exist
char	*strrebuild(char *src1, char *src2, char *src3);

// remove quotes
char	*remove_quotes(char *input);

// parsing
int		parse_cmd(void);
char	*parse_param(char *str, size_t *start);
size_t	find_param_end(char *input, size_t position);
int		is_block_start(char c);
size_t	find_block_end(char *input, size_t position);

// memory free
void	init_signals(void);
int		clear_all(void);
void	clear_exit(void);
void	clear_env(void);
// void	clear_envp(char **array, size_t i);		// never used

// exec
void	route_exec(void);						// doesn't exist
// void	exec(t_scmd *scmd, t_env *env); 		// doesn't exist
// void	route_exec(char **envp);				// never used
// void	exec_full(size_t index, char **args);	// never used
char	**find_in_tab(t_scmd *s_cmd, int fd);

// builtins
char	**buildins_pwd(t_scmd *scmd, char **args);
char	**buildins_cd(t_scmd *scmd, char **args);
char	**builtin_unset(t_scmd *scmd, char **args);
char	**buildins_echo(t_scmd *scmd, char **args);
// int		is_option_ok(char *str);
char	**builtins_export(t_scmd *scmd, char **args);
char	**builtins_env(t_scmd *scmd, char **args);
char	**builtins_exit(t_scmd *scmd, char **args);
// void	is_builtin(t_scmd *s_cmd, char **args, char *target); // never used

// realloc
char	**ft_realloc(char **tab, char *str);
char	*ft_copy(char *str);

// utils
char	*remove_spaces(char *str);
int		is_in_quote(const char *s, int index);
char	*first_word(char *str);

// size_t	charsslen(int fd);
// char	**realloc_heredoc(char **tab, size_t res_len, char *input);	// never used

// error handling
int		error_malloc(int n);

// debug
void	print_cmd(size_t i);
void	print_redir(t_scmd	*s_cmd, size_t i);
void	print_tokens(t_scmd *scmd);
void	print_env_array(char **envp);
void	print_env_list();
void	print_array(char **array, char *str);

// void	rl_replace_line (const char *text, int clear_undo); // never used


// new
void	__exec_full(size_t index, char **args);
int		find_builtin(t_scmd *s_cmd);
char	**route_builtins(t_scmd *scmd, size_t i, char **args);
char	**pipeline(t_scmd	*scmd, char **args, void(foutput)(t_scmd *, char **));
char	*find_path(t_scmd *scmd);

// useful functions
int		ft_strisalpha(char *str);
size_t	find_char(char *str, char c);
char	*fillstr(size_t start, size_t end, const char *src);
char	**split_once(char *str, char c);
char	*ft_strcopy(char *dest, char *src, size_t index_dest);
int		clear_array(char **array, size_t len);
int		ft_strcompare(const char *str, char *test);
size_t	ft_arrlen(char **arr);

#endif
