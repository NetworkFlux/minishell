/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:06:25 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/19 18:52:14 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_exit(void)
{
	clear_all();
	clear_env();
	free(g_fcmd);
	g_fcmd = NULL;
	printf("<clear_exit> ---- done\n");	// remove
	exit(0);
}

void	ctrlc(int sig)
{
	// WARNING! not sure about the fd
	if (sig == SIGINT)
	{
		clear_all();
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// CTRL+C OK
// CTRL+\ OK
void	init_signals(void)
{
	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, SIG_IGN);
}
