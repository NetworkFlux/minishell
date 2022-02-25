/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:11:33 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/25 23:28:09 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void	clear_redir(t_redir *redir)
{
	if (redir->in_args)
		free(redir->in_args);
	if (redir->inin_args)
		free(redir->inin_args);
	if (redir->out_args)
		free(redir->out_args);
	if (redir->outout_args)
		free(redir->outout_args);
	free(redir);
}

int	clear_all(void)
{
	size_t	i;

	if (g_fcmd)
	{
		if(g_fcmd->s_cmd)
		{
			if (g_fcmd->s_cmd[0])
			{
				i = 0;
				while (i < g_fcmd->nb_scmd)
				{
					if (g_fcmd->s_cmd[i]->tokens)
						free(g_fcmd->s_cmd[i]->tokens);
					if (g_fcmd->s_cmd[i]->redir)
						clear_redir(g_fcmd->s_cmd[i]->redir);
					if (g_fcmd->s_cmd[i]->exec)
						free(g_fcmd->s_cmd[i]->exec);
					free(g_fcmd->s_cmd[i]->s_cmd);
					free(g_fcmd->s_cmd[i]);
					i++;
				}
			}
			free(g_fcmd->s_cmd);
			g_fcmd->s_cmd = NULL;
		}
		free (g_fcmd);
		g_fcmd = NULL;
	}
	printf(">> ALL cleared ! <<\n");
	return (0);
}

static void	test(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	(void) info;
	(void) sig;
	clear_all();
	exit (0);
}

void	clear_on_kill(void)
{
	struct sigaction	clear;

	clear.sa_flags = SA_SIGINFO;
	clear.sa_sigaction = test;
	// CTRL+C SIGINT
	// CTRL+\ (qwerty) CTRL+* (on azerty) SIGQUIT
	if (sigaction(SIGINT, &clear, NULL) == -1)
		printf("SIGINT ERROR\n");
	else
		printf("SIGINT OK\n");
	if (sigaction(SIGQUIT, &clear, NULL) == -1)
		printf("SIGQUIT ERROR\n");
	else
		printf("SIGQUIT OK\n");
}
