/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:10:45 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/22 13:54:56 by fcaquard         ###   ########.fr       */
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

void	buildins_cd(t_scmd *scmd)
{
	int	res;

	if (scmd->ntokens == 1)
	{
		res = chdir(getenv("HOME"));
		return ;
	}
	else
	{
		scmd->tokens[1] = check_tilde(scmd->tokens[1]);
		res = chdir(scmd->tokens[1]);
	}
	if (res == -1)
		printf("bash: cd: %s: No such file or directory\n", scmd->tokens[1]);
}
