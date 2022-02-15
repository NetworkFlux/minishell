#include "minishell.h"

void	clean_commands(f_cmd_t *f_cmd)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*temp;

	i = 0;
	while (i < f_cmd->nb_scmd)
	{
		temp = f_cmd->alls_cmd[i].s_cmd;
		j = 0;
		k = 0;
		while (f_cmd->alls_cmd[i].s_cmd[j])
		{
			if (f_cmd->alls_cmd[i].s_cmd[0] == ' ')
				j++;
			temp[k] = f_cmd->alls_cmd[i].s_cmd[j];
			j++;
			k++;
		}
		temp[k] = '\0';
		f_cmd->alls_cmd[i].s_cmd = temp;
		i++;
	}
}