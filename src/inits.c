#include "minishell.h"

f_cmd_t	*init_full_cmd(char *cmd)
{
	f_cmd_t	*res;

	res = malloc(sizeof(f_cmd_t));
	res->f_cmd = cmd;
	res->nb_scmd = countwords_quote((const char *)cmd, '|');
	res->alls_cmd = malloc(sizeof(s_cmd_t) * res->nb_scmd);
	return (res);
}
