/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:11:33 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/25 16:40:57 by fcaquard         ###   ########.fr       */
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

int	clear_all(f_cmd_t *fcmd)
{
	size_t	i;
	size_t	j;

	if (fcmd->s_cmd)
	{
		if (fcmd->s_cmd[0])
		{
			i = 0;
			while (i < fcmd->nb_scmd)
			{
				if (fcmd->s_cmd[i]->tokens)
				{
					if (fcmd->s_cmd[i]->tokens[0])
					{
						j = 0;
						while (j < fcmd->s_cmd[i]->ntokens)
						{
							free(fcmd->s_cmd[i]->tokens[j]->token);
							free(fcmd->s_cmd[i]->tokens[j]);
							j++;
						}
						free(fcmd->s_cmd[i]->tokens);
					}
				}
				free(fcmd->s_cmd[i]->exec);
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
	// should also do CTRL+\ SIGQUIT
	if (sigaction(SIGINT, &clear, NULL) == -1)
	{
		printf("sigaction NONO\n");
	}
	else
	{
		printf("sigaction OKOK\n");
	}
}
