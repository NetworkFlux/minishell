/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:06:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/26 22:27:37 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(void)
{
	size_t	i;

	i = 0;
	if (g_fcmd->nb_scmd && g_fcmd->s_cmd)
	{
		while (g_fcmd->s_cmd[i] && i < g_fcmd->nb_scmd)
		{
			// printf("env: |%s|\n",getenv("PATH"));
			printf(">> EXEC: |%s|\n", g_fcmd->s_cmd[i]->exec);
			g_fcmd->s_cmd[i]->child_id = fork();
			if (g_fcmd->s_cmd[i]->child_id == -1)
			{
				printf("fork failed\n");
				return ;
			}
			if (g_fcmd->s_cmd[i]->child_id == 0) // in fork
			{
				printf("in child process sleep()\n");
				sleep(10);
				exit(0); // terminates the fork
			}
			else	// in main process
			{
				printf("in main process %d\n", g_fcmd->s_cmd[i]->child_id);
				waitpid(g_fcmd->s_cmd[i]->child_id, NULL, 0); // waits for the child to terminate
				g_fcmd->s_cmd[i]->child_id = 0;
				printf("after waiting %d\n", g_fcmd->s_cmd[i]->child_id);
			}
			printf("after fork\n");
			i++;
		}
	}
}
