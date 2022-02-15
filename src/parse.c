#include "minishell.h"

void	parse(f_cmd_t *f_cmd)
{
	char	**split_cmd;
	size_t	i;

	split_cmd = ft_split(f_cmd->f_cmd, '|');
	i = 0;
	while (i < f_cmd->nb_scmd)
	{
		f_cmd->alls_cmd[i].s_cmd = split_cmd[i];
		i++;
	}
	clean_commands(f_cmd);
	//test affichage
	i = 0;
	while (i < f_cmd->nb_scmd)
		ft_putendl_fd(f_cmd->alls_cmd[i++].s_cmd, 1);
}
