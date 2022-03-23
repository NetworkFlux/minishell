/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:50:19 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/23 20:47:49 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* prints the name of the current directory */
// Probably not a good way to output it
// Should test if it works alongside with `cd`
void	output_pwd(t_scmd *scmd)
{
	char	*pwd;

	(void)scmd;
	if (redir_files_ok(scmd) < 0)
		exit(1);
	pwd = getcwd(NULL, sizeof(NULL) * ft_strlen(NULL));
	ft_putendl_fd(pwd, 1);
	free(pwd);
	exit(0);
}

int	buildins_pwd(t_scmd *scmd, int readpipe)
{
	return (pipeline(scmd, &output_pwd, readpipe));
}
