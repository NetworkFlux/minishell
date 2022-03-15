/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:06:25 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/15 16:58:42 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_exit(void)
{
	clear_all();
	clear_env();
	free (g_fcmd);
	g_fcmd = NULL;
	printf("<clear_all> wiped !\n");
	exit(0);
}

// WARNING! not sure about the fd
void	ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		clear_all();
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putstr_fd(" \b\b", 1);
	}
}

// CTRL+C OK
// CTRL+\ OK
void	init_signals(void)
{
	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, SIG_IGN);
}
