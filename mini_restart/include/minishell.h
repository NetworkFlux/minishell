#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"

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
int		is_block_start(char c);
char	*total_input(char *cmd, char *completion);

// init
f_cmd_t	*init_full_cmd(char *cmd);
redir_t	*init_redir(void);;

// parse redir
void	parse_redir(f_cmd_t *f_cmd);
int		nb_redir(char *str, char c);
int		nb_dredir(char *str, char c);
void	fill_redir(s_cmd_t *s_cmd);
void	fill_s(s_cmd_t *s_cmd, char c);
void	fill_d(s_cmd_t *s_cmd, char c);
void	add_redir_arg(s_cmd_t *s_cmd, unsigned int i, int j, char c);
void	add_dredir_arg(s_cmd_t *s_cmd, unsigned int i, int j, char c);

void	print_redir(s_cmd_t	*s_cmd, size_t i);

// utils
char	*remove_spaces(char *str);
int		is_in_quote(const char *s, int index);
char	*first_word(char *str);

#endif