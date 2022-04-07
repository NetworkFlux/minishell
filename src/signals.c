/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:06:25 by fcaquard          #+#    #+#             */
/*   Updated: 2022/04/07 12:48:58 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		if (g_fcmd->active_heredoc != -1)
		{
			if (g_fcmd->s_cmd[g_fcmd->active_heredoc]->pid == 0)
			{
				close(0);
				exit(130);
			}
			else
			{
				unlink(g_fcmd->s_cmd[g_fcmd->active_heredoc]->redir->here_name);
				free(g_fcmd->s_cmd[g_fcmd->active_heredoc]->redir->here_name);
				g_fcmd->s_cmd[g_fcmd->active_heredoc]->redir->here_name = NULL;
			}
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
