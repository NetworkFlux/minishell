/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:06:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/26 18:11:24 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(void)
{
	size_t	i;
	pid_t	pid;

	i = 0;
	if (g_fcmd->nb_scmd && g_fcmd->s_cmd)
	{
		while (g_fcmd->s_cmd[i] && i < g_fcmd->nb_scmd)
		{
			printf(">> EXEC: |%s|\n", g_fcmd->s_cmd[i]->exec);
			pid = fork();
			if (pid == -1)
			{
				printf("fork failed\n");
				return ;
			}
			if (pid == 0)
			{
				printf("in child process\n");
				sleep(1);
			}
			waitpid(pid, NULL, 0);
			printf("in main process\n");
			i++;
		}
	}
}
