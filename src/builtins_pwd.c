/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:50:19 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/22 14:04:04 by fcaquard         ###   ########.fr       */
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

void	buildins_pwd(t_scmd *scmd)
{
	pipeline(scmd, &output_pwd);
}
