/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:06:25 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/22 10:13:28 by fcaquard         ###   ########.fr       */
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
	// struct termios	*termios_p;
	// int		tty_fd;
	// char	*tty;
	// // int		control;

	// termios_p = malloc(sizeof(struct termios));
	// if (!termios_p)
	// 	return ;

	// tty_fd = ttyslot();
	// printf("ttyslot: %d\n", tty_fd);
	// if (tty_fd > -1)
	// {
	// 	tty = ttyname(tty_fd);
	// 	printf("name: %s\n", tty);
	// 	if (tcgetattr(tty_fd, termios_p) != -1)
	// 	{
	// 		termios_p->c_cflag |= ECHO;
	// 		tcsetattr(tty_fd, TCSANOW, termios_p);
	// 		printf("OK\n");
	// 	}
	// }
	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, SIG_IGN);
}
