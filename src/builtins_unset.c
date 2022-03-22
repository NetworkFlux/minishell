/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:44:17 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/22 13:58:08 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set the desired env variable to \0 if found
void	builtin_unset(t_scmd *scmd)
{
	t_env	*tmp;

	if (scmd->ntokens != 2
		|| !scmd->tokens
		|| !scmd->tokens[1])
	{
		return ;
	}
	tmp = find_env(g_fcmd->envp, scmd->tokens[1]);
	if (tmp)
		g_fcmd->envp = remove_env(tmp);
}
