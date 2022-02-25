#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"

typedef struct REDIRECTION
{
	int		out;
	char	**out_args;
	int		outout;
	char	**outout_args;
	int		in;
	char	**in_args;
	int		inin;
	char	**inin_args;
}	redir_t;

typedef	enum	s_blocktype
{
	singleq = 0,
	doubleq = 1,
	paranthesis = 2
}	e_blocktype;

typedef	enum	s_exectype
{
	builtin = 0,
	extrenal = 1,
	path = 2
}	e_exectype;

typedef	struct s_token
{
	char		*token;
	e_blocktype	type;
}	t_token;


typedef struct SINGLE_CMD
{
	char		*s_cmd;		// single command
	char		*exec;		// program to be called
	e_exectype	type;
	t_token		**tokens;	// list of tokens following
	size_t		ntokens;	// number of tokens (size of tokens array)
	redir_t		redir;
}	s_cmd_t;

typedef struct FULL_CMD
{
	char 	*f_cmd;		// full command (all the input)
	size_t	nb_scmd;	// number of single commands
	s_cmd_t	**s_cmd;	// array of single commands
}	f_cmd_t;

// main
char	*take_input(void);

// inits
f_cmd_t	*init_full_cmd(char *cmd);

// parse
void	parse(f_cmd_t *f_cmd);
void	parse_scom(s_cmd_t *f_cmd);

int		parse_alt(f_cmd_t *f_cmd);
int		is_input_incomplete(char *input);
int		count_input(s_cmd_t *s_cmd, size_t start);
int		parse_param(s_cmd_t *s_cmd, size_t *start, int *is_command, size_t *i);
size_t	find_param_end(char *input, size_t position);
int		is_block_start(char c);
int		parse_block(s_cmd_t *s_cmd, size_t *start, int *is_command, size_t *i);
size_t	find_block_end(char *input, size_t position);
int		is_delimiter(int c);
int		parse_delimiter(s_cmd_t *s_cmd, size_t *start, int *is_command, size_t *i);
size_t	find_delimiter_end(char *input, size_t start);
char	*tokenize(char *input, size_t start, size_t end);


//utils
void	clean_commands(f_cmd_t *f_cmd);
char	*first_word(char *str);
char	*skip_word(char *str);
void	print_cmd(s_cmd_t s_cmd);

#endif