/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:50:19 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/05 15:29:04 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* prints the name of the current directory */
// Probably not a good way to output it
// Should test if it works alongside with `cd`
void	buildins_pwd(t_scmd *scmd, int fd_out)
{
	char	*res;

	res = NULL;
	if (scmd->ntokens != 0)
	{
		printf("<pwd> Too many arguments\n");
		return ;
	}
	ft_putendl_fd(getcwd(res, sizeof(res)), fd_out);
	if (fd_out > 2)
		close(fd_out);
	return ;
}