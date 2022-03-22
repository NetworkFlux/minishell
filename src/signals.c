/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:06:25 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/22 17:34:41 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_exit(int	n)
{
	clear_all();
	clear_env();
	free(g_fcmd);
	g_fcmd = NULL;
	exit(n);
}

void	ctrlc(int sig)
{
	// WARNING! not sure about the fd
	if (sig == SIGINT)
	{
		if (!kill_child())
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			write(1, "\n", 1);
		}
	}
}

// CTRL+C OK
// CTRL+\ OK
void	init_signals(void)
{
	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, SIG_IGN);
}
