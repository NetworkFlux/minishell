/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:56:38 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/03 17:43:44 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void print_envp()
{
	size_t i;
	
	i = 0;
	while (g_fcmd->envp[i])
	{
		printf("|%s|\n", g_fcmd->envp[i]);
		i++;
	}
}

/* NOT WORKING YET */
void	builtins_export(t_scmd *scmd)
{
	size_t	i;

	i = 0;

	if (scmd->ntokens == 0)
	{
		print_envp();
		return ;
	}

	if (scmd->ntokens != 1
		|| !scmd->tokens
		|| !scmd->tokens[0]
		|| !scmd->tokens[0]->token)
	{
		printf ("error arguments.\n");
		return ;
	}
	
	while (g_fcmd->envp[i])
	{
		i++;
	}
	printf("i: %ld\n", i);
	// g_fcmd->envp[i] = scmd->tokens[0]->token;
	print_envp();
}
