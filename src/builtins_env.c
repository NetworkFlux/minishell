/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 11:10:03 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/08 11:17:24 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_env(t_scmd *scmd, int fd_out)
{
	g_fcmd->envp = env_first(g_fcmd->envp);

	if (redir_files_ok(scmd) < 0)
		return;
	while (g_fcmd->envp)
	{
		ft_putstr_fd(g_fcmd->envp->name, fd_out);
		ft_putchar_fd('=', fd_out);
		ft_putendl_fd(g_fcmd->envp->value, fd_out);
		if (!g_fcmd->envp->next)
			break ;
		g_fcmd->envp = g_fcmd->envp->next;
	}
}
