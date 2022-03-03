/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:44:17 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/03 17:12:10 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set the desired env variable to \0 if found
void	builtin_unset(t_scmd *scmd)
{
	size_t	i;

	i = 0;
	if (scmd->ntokens == 1 && scmd->tokens[0] && scmd->tokens[0]->token)
	{
		if (scmd->tokens[0]->token[0] == '-')
		{
			printf("invalid option\n");
			return ;
		}
		while (g_fcmd->envp[i])
		{
			if (find_env_variable(g_fcmd->envp[i], scmd->tokens[0]->token) != 0)
			{
				g_fcmd->envp[i] = NULL;
				return ;
			}
			i++;
		}
	}
	else
		printf("error arguments\n");
	return ;
}
