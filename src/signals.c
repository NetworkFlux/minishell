/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:06:25 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/05 15:08:11 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear_exit(void)
{
	clear_all();
	clear_env();
	free (g_fcmd);
	g_fcmd = NULL;
	printf("<clear_all> wiped !\n");
	exit(0);
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
static void	do_nothing(int sig, siginfo_t *info, void *ucontext)
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
	// looking to handle CTRL+D using tty and ioctl
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
