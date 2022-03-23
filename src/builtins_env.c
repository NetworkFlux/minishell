/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 11:10:03 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/23 12:06:50 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// called from child process
void	output_env(t_scmd *scmd)
{
	if (redir_files_ok(scmd) < 0)
		exit(1);
	while (g_fcmd->envp)
	{
		ft_putstr_fd(g_fcmd->envp->name, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(g_fcmd->envp->value, 1);
		if (!g_fcmd->envp->next)
			break ;
		g_fcmd->envp = g_fcmd->envp->next;
	}
	exit(0);
}

int	builtins_env(t_scmd *scmd, int readpipe)
{
	g_fcmd->envp = env_first(g_fcmd->envp);
	return (pipeline(scmd, &output_env, readpipe));
}
