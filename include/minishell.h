#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"

typedef struct SINGLE_CMD
{
	char	*s_cmd;
	char	*ex_cmd;
	char	*options;
	char	**args;
	int		nb_args;
}s_cmd_t;

typedef struct FULL_CMD
{
	char	*f_cmd;
	size_t	nb_scmd;
	s_cmd_t	*alls_cmd;

	size_t	ntokens;
	size_t	ncmd;
	size_t	itoken;
	char	**tokens;
}f_cmd_t;

// main
char	*take_input(void);

// inits
f_cmd_t	*init_full_cmd(char *cmd);

// parse
void	parse(f_cmd_t *f_cmd);
void	parse_scom(s_cmd_t *f_cmd);

int		parse_alt(f_cmd_t *f_cmd);
int		is_input_incomplete(char *input);
int		count_input(f_cmd_t *f_cmd, size_t start);
int		parse_param(f_cmd_t *f_cmd, size_t *start, int *is_command);
size_t	find_param_end(char *input, size_t position);
int		is_block_start(char c);
int		parse_block(f_cmd_t *f_cmd, size_t *start, int *is_command);
size_t	find_block_end(char *input, size_t position);
int		is_delimiter(int c);
int		parse_delimiter(f_cmd_t *f_cmd, size_t *start, int *is_command);
size_t	find_delimiter_end(char *input, size_t start);
char	*tokenize(char *input, size_t start, size_t end);


//utils
void	clean_commands(f_cmd_t *f_cmd);
char	*first_word(char *str);
char	*skip_word(char *str);
void	print_cmd(s_cmd_t s_cmd);

#endif