#include "minishell.h"

void	print_cmd(s_cmd_t s_cmd)
{
	int	i;

	i = 0;
	printf("FULL COMMAND : %s\n", s_cmd.s_cmd);
	printf("Exectuable command : %s\n", s_cmd.ex_cmd);
	printf("Options : %s\n", s_cmd.options);
	printf("Number of arguments : %d\n", s_cmd.nb_args);
	printf("Arguments :\n");
	while (i < s_cmd.nb_args)
	{
		printf("Argument %d: %s\n", i, s_cmd.args[i]);
		i++;
	}
}

char	*skip_word(char *str)
{
	char	*res;

	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i] == ' ')
		i++;
	while (str[i] != ' ')
		i++;
	res = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!res)
		return (NULL);
	i++;
	while (str[i])
	{
		res[j] = str[i++];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*first_word(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[0] == ' ')
	{
		j = 1;
		i++;
	}
	while (str[i] != ' ')
		i++;
	res = malloc(sizeof(char) * (i - j + 1));
	if (!res)
		return (NULL);
	i = j;
	j = 0;
	while (str[i] != ' ')
	{
		res[j] = str[i++];
		j++;
	}
	res[j] = '\0';
	return (res);
}

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