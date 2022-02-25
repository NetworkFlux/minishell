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


typedef struct REDIRECTION
{
	size_t		out;
	size_t		outout;
	size_t		in;
	size_t		inin;
	char	**out_args;
	char	**outout_args;
	char	**in_args;
	char	**inin_args;
}redir_t;

typedef struct SINGLE_CMD
{
	char	*s_cmd;
	char	*exec;
	size_t	ntokens;
	t_token	**tokens;
	redir_t	*redir;
}s_cmd_t;

typedef struct FULL_CMD
{
	char	*f_cmd;
	size_t	nb_scmd;
	s_cmd_t	**s_cmd;

}f_cmd_t;


// take_input
char	*take_input(void);
int		is_input_incomplete(char *input);

// init
f_cmd_t	*init_full_cmd(char *cmd);
redir_t	*init_redir(void);;

// parse redir
int		parse_redir(f_cmd_t *f_cmd);
int		nb_redir(char *str, char c);
int		nb_dredir(char *str, char c);
void	fill_redir(s_cmd_t *s_cmd);
void	fill_s(s_cmd_t *s_cmd, char c);
void	fill_d(s_cmd_t *s_cmd, char c);
void	add_redir_arg(s_cmd_t *s_cmd, unsigned int i, int j, char c);
void	add_dredir_arg(s_cmd_t *s_cmd, unsigned int i, int j, char c);

void	print_redir(s_cmd_t	*s_cmd, size_t i);

// parsing
int		parse_alt(f_cmd_t *f_cmd);
int		count_input(s_cmd_t *s_cmd, size_t start);
int		parse_param(s_cmd_t *s_cmd, size_t *start, int *is_command, size_t *i);
size_t	find_param_end(char *input, size_t position);
int		is_block_start(char c);
int		parse_block(s_cmd_t *s_cmd, size_t *start, int *is_command, size_t *i);
size_t	find_block_end(char *input, size_t position);
int		is_delimiter(int c);
char	*tokenize(char *input, size_t start, size_t end);
// int		parse_delimiter(s_cmd_t *s_cmd, size_t *start, int *is_command, size_t *i);
// size_t	find_delimiter_end(char *input, size_t start);

// memory free
void	clear_on_kill(void);
int		clear_all(f_cmd_t *fcmd);

// utils
char	*remove_spaces(char *str);
int		is_in_quote(const char *s, int index);
char	*first_word(char *str);

#endif