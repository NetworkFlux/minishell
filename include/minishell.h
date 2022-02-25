#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"

typedef enum s_blocktype
{
	undefined = 0,
	singleq = 1,
	doubleq = 2,
	parenthesis = 3
} e_blocktype;

typedef struct	s_token
{
	char 		*token;
	e_blocktype	type;
}	t_token;

typedef struct s_redirection
{
	size_t		out;
	size_t		outout;
	size_t		in;
	size_t		inin;
	char	**out_args;
	char	**outout_args;
	char	**in_args;
	char	**inin_args;
}	t_redir;

typedef struct s_single_command
{
	char	*s_cmd;
	char	*exec;
	size_t	ntokens;
	t_token	**tokens;
	t_redir	*redir;
}	t_scmd;

typedef struct s_full_command
{
	char	*f_cmd;
	size_t	nb_scmd;
	t_scmd	**s_cmd;
}	t_fcmd;

// take_input
char	*take_input(void);
int		is_input_incomplete(char *input);

// init
t_fcmd	*init_full_cmd(char *cmd);
t_redir	*init_redir(void);;

// parse redir
int		parse_redir(t_fcmd *f_cmd);
int		nb_redir(char *str, char c);
int		nb_dredir(char *str, char c);
void	fill_redir(t_scmd *s_cmd);
void	fill_s(t_scmd *s_cmd, char c);
void	fill_d(t_scmd *s_cmd, char c);
void	add_redir_arg(t_scmd *s_cmd, unsigned int i, int j, char c);
void	add_dredir_arg(t_scmd *s_cmd, unsigned int i, int j, char c);

void	print_redir(t_scmd	*s_cmd, size_t i);

// parsing
int		parse_alt(t_fcmd *f_cmd);
int		count_input(t_scmd *s_cmd, size_t start);
int		parse_param(t_scmd *s_cmd, size_t *start, int *is_command, size_t *i);
size_t	find_param_end(char *input, size_t position);
int		is_block_start(char c);
int		parse_block(t_scmd *s_cmd, size_t *start, int *is_command, size_t *i);
size_t	find_block_end(char *input, size_t position);
int		is_delimiter(int c);
char	*tokenize(char *input, size_t start, size_t end);
// int		parse_delimiter(t_scmd *s_cmd, size_t *start, int *is_command, size_t *i);
// size_t	find_delimiter_end(char *input, size_t start);

// memory free
void	clear_on_kill(void);
int		clear_all(t_fcmd *fcmd);

// utils
char	*remove_spaces(char *str);
int		is_in_quote(const char *s, int index);
char	*first_word(char *str);

#endif