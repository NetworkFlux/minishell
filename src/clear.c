/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:11:33 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/25 21:53:48 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void	test(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	(void) info;
	(void) sig;
	printf("CLEARING... Needs f_cmd :/ \n");
	// clear_all(fcmd);
	exit (0);
}

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

int	clear_all(t_fcmd *fcmd)
{
	size_t	i;

	if (fcmd->s_cmd)
	{
		if (fcmd->s_cmd[0])
		{
			i = 0;
			while (i < fcmd->nb_scmd)
			{
				if (fcmd->s_cmd[i]->tokens)
					free(fcmd->s_cmd[i]->tokens);
				if (fcmd->s_cmd[i]->redir)
					clear_redir(fcmd->s_cmd[i]->redir);
				free(fcmd->s_cmd[i]->exec);
				free(fcmd->s_cmd[i]->s_cmd);
				free(fcmd->s_cmd[i]);
				i++;
			}
		}
		free(fcmd->s_cmd);
	}
	free (fcmd);
	return (0);
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
