/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:10:45 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/21 17:04:36 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*check_tilde(char *path)
{
	char	*home;
	char	*res;
	int		i;
	int		begin;
	int		changed;

	home = getenv("HOME");
	i = 0;
	begin = 0;
	changed = 0;
	while(path[i])
	{
		if (path[i] == '~')
		{
			res = ft_strcat(ft_substr(path, begin, i), home);
			res = ft_strcat(res, ft_substr(path, i + 1, ft_strlen(path)));
			begin = i;
			changed = 1;
		}
		i++;
	}
	if (!changed)
		return (path);
	return (res);
}

char **buildins_cd(t_scmd *scmd, char **args)
{
	(void)args;
	int	res;

	if (scmd->ntokens == 1)
	{
		res = chdir(getenv("HOME"));
		return (args);
	}
	else
	{
		scmd->tokens[1] = check_tilde(scmd->tokens[1]);
		res = chdir(scmd->tokens[1]);
	}
	if (res == -1)
		printf("bash: cd: %s: No such file or directory\n", scmd->tokens[1]);
	return (args);
}
