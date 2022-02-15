#include "minishell.h"

f_cmd_t	*init_full_cmd(char *cmd)
{
	f_cmd_t	*res;
	int		i;

	res = malloc(sizeof(f_cmd_t));
	res->f_cmd = cmd;
	res->nb_scmd = 1;
	i = 0;
	while (res->f_cmd[i])
	{
		if (res->f_cmd[i] == '|')
			res->nb_scmd++;
		i++;
	}
	res->alls_cmd = malloc(sizeof(s_cmd_t) * res->nb_scmd);
	return (res);
}
