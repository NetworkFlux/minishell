#include "minishell.h"
/*
void	parse_scom(s_cmd_t *s_cmd)
{
	char	*temp;

	temp = s_cmd->s_cmd;
	s_cmd->ex_cmd = first_word(temp);
	temp = skip_word(temp);
	if (temp && temp[0] == '-')
	{
		s_cmd->options = first_word(temp);
		temp = skip_word(temp);
	}
	else
		s_cmd->options = NULL;
	s_cmd->nb_args = countwords_quote(temp, ' ');
	s_cmd->args = ft_split_quote(temp, ' ');
}

void	parse(f_cmd_t *f_cmd)
{
	char	**split_cmd;
	size_t	i;

	split_cmd = ft_split_quote(f_cmd->f_cmd, '|');
	i = 0;
	while (i < f_cmd->nb_scmd)
	{
		f_cmd->alls_cmd[i].s_cmd = split_cmd[i];
		parse_scom(&f_cmd->alls_cmd[i]);
		i++;
	}
	clean_commands(f_cmd);
	//test affichage
	i = 0;
	while (i < f_cmd->nb_scmd)
	{
		ft_putendl_fd("Command ", 1);
		ft_putnbr_fd(i, 1);
		ft_putchar_fd('\n', 1);
		print_cmd(f_cmd->alls_cmd[i]);
		i++;
	}
}
*/