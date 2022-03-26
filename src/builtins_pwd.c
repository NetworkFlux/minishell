/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:50:19 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/26 14:35:24 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* prints the name of the current directory */
// Probably not a good way to output it
// Should test if it works alongside with `cd`
void	output_pwd(t_scmd *scmd)
{
	t_env	*tmp;
	char	*pwd;

	(void)scmd;
	tmp = NULL;
	if (redir_files_ok(scmd) < 0)
		exit(1);
	pwd = getcwd(NULL, sizeof(NULL) * ft_strlen(NULL));
	if (!pwd && errno == 2)
	{
		tmp = find_env(g_fcmd->envp, "PWD");
		pwd = tmp->value;
	}
	ft_putendl_fd(pwd, 1);
	free(tmp);
	free(pwd);
	exit(0);
}

int	buildins_pwd(t_scmd *scmd, int readpipe)
{
	return (pipeline(scmd, &output_pwd, readpipe));
}
