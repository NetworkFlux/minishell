/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:10:45 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/22 19:26:35 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*check_tilde(char *path, int i, int begin)
{
	char	*home;
	char	*tmp;
	char	*tmp2;
	char	*res;

	home = getenv("HOME");
	res = NULL;
	while(path[i])
	{
		if (path[i] == '~')
		{
			tmp = ft_substr(path, begin, i);
			tmp2 = ft_strcat(tmp, home);
			free(tmp);
			tmp = ft_substr(path, i + 1, ft_strlen(path));
			res = ft_strcat(tmp2, tmp); // we should make a strcat that frees its inputs
			free(tmp2);
			free(tmp);
			begin = i;
		}
		i++;
	}
	if (!res)
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
		scmd->tokens[1] = check_tilde(scmd->tokens[1], 0, 0);
		res = chdir(scmd->tokens[1]);
		insert_update_env("PWD", getcwd(NULL, sizeof(NULL) * ft_strlen(NULL)));
	}
	if (res == -1)
	{
		write(2, "bash: cd: ", 10);
		write(2,  scmd->tokens[1], ft_strlen(scmd->tokens[1]));
		write(2, ": Not a directory\n", 18);
	}
}
