/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:11:33 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/26 23:21:32 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	clear_scmd(void)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd)
	{
		if (g_fcmd->s_cmd[i]->tokens)
			free(g_fcmd->s_cmd[i]->tokens);
		if (g_fcmd->s_cmd[i]->redir)
			clear_redir(g_fcmd->s_cmd[i]->redir);
		if (g_fcmd->s_cmd[i]->exec)
			free(g_fcmd->s_cmd[i]->exec);
		if (g_fcmd->s_cmd[i]->child_id != 0)
		{
			kill (g_fcmd->s_cmd[i]->child_id, SIGKILL);
			g_fcmd->s_cmd[i]->child_id = 0;
			printf(">> fork cleared ! <<\n");
		}
		free(g_fcmd->s_cmd[i]->s_cmd);
		free(g_fcmd->s_cmd[i]);
		i++;
	}
}

int	clear_all(void)
{
	if (g_fcmd)
	{
		if (g_fcmd->s_cmd)
		{
			if (g_fcmd->s_cmd[0])
				clear_scmd();
			free(g_fcmd->s_cmd);
			g_fcmd->s_cmd = NULL;
		}
		free (g_fcmd);
		g_fcmd = NULL;
	}
	printf(">> ALL cleared ! <<\n");
	return (0);
}

static void	clear_signal_sent(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	(void) info;
	(void) sig;
	clear_all();
	exit (0);
}

// Clears on signals / CTRL+C SIGINT
// CTRL+\ (qwerty) CTRL+* (on azerty) SIGQUIT
void	clear_on_signal(void)
{
	struct sigaction	clear;

	clear.sa_flags = SA_SIGINFO;
	clear.sa_sigaction = clear_signal_sent;
	if (sigaction(SIGINT, &clear, NULL) == -1)
		printf("SIGINT ERROR\n");
	else
		printf("SIGINT OK\n");
	if (sigaction(SIGQUIT, &clear, NULL) == -1)
		printf("SIGQUIT ERROR\n");
	else
		printf("SIGQUIT OK\n");
}
