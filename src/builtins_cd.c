/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:10:45 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/26 19:26:56 by fcaquard         ###   ########.fr       */
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

static void	update_pwds(void)
{
	char	*pwd;
	t_env	*tmp;

	pwd = getcwd(NULL, sizeof(NULL) * ft_strlen(NULL));
	if (pwd)
	{
		tmp = find_env(g_fcmd->envp, "PWD");
		if (tmp)
			insert_update_env("OLDPWD", tmp->value);
		else
			insert_update_env("OLDPWD", pwd);
		insert_update_env("PWD", pwd);
		free(pwd);
	}
	else
	{
		free(pwd);
		errno = ENOENT;
		perror("cd: error retrieving current directory: \
			getcwd: cannot access parent directories");
	}
}

static void	cd_with_args(t_scmd *scmd, int *res, t_env *tmp)
{
	if (ft_strncmp(scmd->tokens[1], "-", 1) == 0)
	{
		if (ft_strlen(scmd->tokens[1]) != 1)
			*res = -1;
		else
		{
			tmp = find_env(g_fcmd->envp, "OLDPWD");
			if (!tmp)
			{
				ft_putstr_fd("bash: cd: OLDPWD not set", 2);
				return ;
			}
			ft_putendl_fd(tmp->value, 1);
			*res = chdir(tmp->value);
		}
	}
	else
	{
		scmd->tokens[1] = check_tilde(scmd->tokens[1], 0, 0, NULL);
		*res = chdir(scmd->tokens[1]);
	}
	update_pwds();
}

void	buildins_cd(t_scmd *scmd)
{
	int		res;
	t_env	*tmp;

	tmp = NULL;
	if (scmd->ntokens == 1)
	{
		res = chdir(getenv("HOME"));
		update_pwds();
		return ;
	}
	else
		cd_with_args(scmd, &res, tmp);
	if (res == -1)
	{
		write(2, "bash: cd: ", 10);
		perr(20, scmd->tokens[1]);
	}
}
