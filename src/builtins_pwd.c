/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:50:19 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/22 15:26:11 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* prints the name of the current directory */
// Probably not a good way to output it
// Should test if it works alongside with `cd`

void	output_pwd(t_scmd *scmd)
{
	(void)scmd;
	if (redir_files_ok(scmd) < 0)
		exit(1);
	ft_putendl_fd(getcwd(NULL, sizeof(NULL) * ft_strlen(NULL)), 1);
	exit(0);
}

int		buildins_pwd(t_scmd *scmd, int readpipe)
{
	return (pipeline(scmd, &output_pwd, readpipe));
}
