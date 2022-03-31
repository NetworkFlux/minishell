/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:06:25 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/31 18:58:28 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		if (g_fcmd->active_heredoc == 1)
		{
			write(1, "\b\b", 2);
			write(1, "  ", 2);
			write(1, "\b\b", 2);
			g_fcmd->active_heredoc = 0;
			exit(130);
			return ;
		}
		write(1, "\n", 1);
		if (!kill_child())
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

// CTRL+C OK
// CTRL+\ OK
void	init_signals(void)
{
	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
