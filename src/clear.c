/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:11:33 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/04 19:35:05 by fcaquard         ###   ########.fr       */
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

/*	loops over single command in order to free its content 
	kill command's child process if still running (pid!=0) */
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
			printf("<clear_scmd> fork cleared\n");
		}
		if (g_fcmd->s_cmd[i]->instructions)
			free(g_fcmd->s_cmd[i]->instructions);
		free(g_fcmd->s_cmd[i]->s_cmd);
		free(g_fcmd->s_cmd[i]);
		i++;
	}
}

/* dives into our command tree and tries to free everything */
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
		// free (g_fcmd);
		// g_fcmd = NULL;
	}
	printf("<clear_all> all cleared\n");
	return (0);
}

/* on SIGINT signal (CTRL+C) */
static void	clear_signal_sent(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	(void) info;
	(void) sig;
	printf("<clear_signal_sent> SIGINT\n");
	clear_all();
	exit (0);
}

/* prevents CTRL+\ to invoke SIGQUIT */
static	void do_nothing(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	(void) info;
	(void) sig;	
	printf("<do_nothing> SIGQUIT\n");
}

/**
 SIGINT:	CTRL+C (should display a new prompt)
 SIGQUIT:	CTRL+\ (should to nothing)
 CTRL+D means EOF and isn't handled with signals but with tty
*/
void	init_signals(void)
{
	struct sigaction	clear;
	struct sigaction	nothing;

	clear.sa_flags = SA_SIGINFO;
	clear.sa_sigaction = clear_signal_sent;
	nothing.sa_flags = SA_SIGINFO;
	nothing.sa_sigaction = do_nothing;
	if (sigaction(SIGINT, &clear, NULL) == -1)
		printf("<init_signals> SIGINT ERROR\n");
	if (sigaction(SIGQUIT, &nothing, NULL) == -1)
		printf("<init_signals> SIGQUIT ERROR\n");

	// looking to handle CTRL+D using tty and ioctl
	int ttyslot_ = ttyslot();
	printf("<init_signals> ttyslot (fd): %d\n", ttyslot_);
	int isatty_ = isatty(ttyslot_);
	if (isatty_)
	{
		char *ttyname_ = ttyname(ttyslot_);
		printf("<init_signals> ttyname (terminal): %s\n", ttyname_);
	}
	else
	{
		printf("<init_signals> fd provided is not a terminal\n");
	}
}
