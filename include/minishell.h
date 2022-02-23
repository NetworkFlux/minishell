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
}f_cmd_t;

// main
char	*take_input(void);

// inits
int		is_input_incomplete(char *input);
f_cmd_t	*init_full_cmd(char *cmd);

// parse
void	parse(f_cmd_t *f_cmd);
void	parse_scom(s_cmd_t *f_cmd);
// parsing alternative test
int		parse_strtok(f_cmd_t *f_cmd);

//utils
void	clean_commands(f_cmd_t *f_cmd);
char	*first_word(char *str);
char	*skip_word(char *str);
void	print_cmd(s_cmd_t s_cmd);

#endif