/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:44:17 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/21 14:46:26 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set the desired env variable to \0 if found
char	**builtin_unset(t_scmd *scmd, char **args)
{
	(void)args;
	t_env	*tmp;

	if (scmd->ntokens != 2
		|| !scmd->tokens
		|| !scmd->tokens[1])
	{
		return (args);
	}
	tmp = find_env(g_fcmd->envp, scmd->tokens[1]);
	if (tmp)
		g_fcmd->envp = remove_env(tmp);
	return (args);
}
