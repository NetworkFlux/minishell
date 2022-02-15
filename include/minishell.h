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
	size_t	nb_args;
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
f_cmd_t	*init_full_cmd(char *cmd);

// parse
void	parse(f_cmd_t *f_cmd);

//utils
void	clean_commands(f_cmd_t *f_cmd);

#endif