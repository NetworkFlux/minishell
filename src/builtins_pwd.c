/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:50:19 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/08 11:02:26 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* prints the name of the current directory */
// Probably not a good way to output it
// Should test if it works alongside with `cd`
void	buildins_pwd(t_scmd *scmd, int fd_out)
{
	char	*res;

	if (redir_files_ok(scmd) < 0)
		return;
	res = NULL;
	if (scmd->ntokens != 1)
	{
		printf("<pwd> Too many arguments\n");
		return ;
	}
	ft_putendl_fd(getcwd(res, sizeof(res) * ft_strlen(res)), fd_out);
	if (fd_out > 2)
		close(fd_out);
	return ;
}
