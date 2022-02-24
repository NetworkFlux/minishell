#include "minishell.h"

f_cmd_t	*init_full_cmd(char *cmd)
{
	f_cmd_t	*res;

	res = malloc(sizeof(f_cmd_t));
	if (!res)
		return (NULL);
	res->f_cmd = cmd;
	res->nb_scmd = countwords_quote((const char *)cmd, '|');
	res->alls_cmd = malloc(sizeof(s_cmd_t) * res->nb_scmd);
	
	res->itoken = 0;
	res->ncmd = 0;
	res->ntokens = 0;
	res->tokens = NULL;
	if (!res->alls_cmd)
	{
		free(res);
		return (NULL);
	}
	return (res);
}
