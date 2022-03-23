/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:10:45 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/23 20:47:51 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*check_tilde(char *path, int i, int begin, char *res)
{
	char	*home;
	char	*tmp;
	char	*tmp2;

	home = getenv("HOME");
	while (path[i])
	{
		if (path[i] == '~')
		{
			tmp = ft_substr(path, begin, i);
			tmp2 = ft_strcat(tmp, home);
			free(tmp);
			tmp = ft_substr(path, i + 1, ft_strlen(path));
			res = ft_strcat(tmp2, tmp);
			free(tmp2);
			free(tmp);
			begin = i;
		}
		i++;
	}
	if (!res)
		return (path);
	free(path);
	return (res);
}

void	buildins_cd(t_scmd *scmd)
{
	int		res;
	t_env	*tmp;
	char	*pwd;

	if (scmd->ntokens == 1)
	{
		res = chdir(getenv("HOME"));
		return ;
	}
	else
	{
		scmd->tokens[1] = check_tilde(scmd->tokens[1], 0, 0, NULL);
		res = chdir(scmd->tokens[1]);
		tmp = find_env(g_fcmd->envp, "PWD");
		if (tmp)
			insert_update_env("OLDPWD", tmp->value);
		pwd = getcwd(NULL, sizeof(NULL) * ft_strlen(NULL));
		insert_update_env("PWD", pwd);
		free(pwd);
	}
	if (res == -1)
	{
		write(2, "bash: cd: ", 10);
		perr(20, scmd->tokens[1]);
	}
}
