/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:50:19 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/17 17:13:47 by fcaquard         ###   ########.fr       */
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
		return ;
	res = NULL;
	if (scmd->ntokens != 1)
	{
		printf("<pwd> Too many arguments\n");
		return ;
	}
	ft_putendl_fd(getcwd(res, sizeof(res) * ft_strlen(res)), 1);
	return ;
}
