/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.42.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:10:45 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/04 18:05:31 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		*res = chdir(scmd->tokens[1]);
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
