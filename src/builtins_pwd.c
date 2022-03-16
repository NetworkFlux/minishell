/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:50:19 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/16 15:29:44 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* prints the name of the current directory */
// Probably not a good way to output it
// Should test if it works alongside with `cd`
void	buildins_pwd(t_scmd *scmd)
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
	ft_putendl_fd(getcwd(res, sizeof(res) * ft_strlen(res)), 1);
	return ;
}