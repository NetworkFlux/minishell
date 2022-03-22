/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:44:17 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/22 19:42:33 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set the desired env variable to \0 if found
void	builtin_unset(t_scmd *scmd)
{
	t_env	*tmp;
	size_t	i;

	i = 1;
	if (scmd->ntokens < 2
		|| !scmd->tokens)
	{
		return ;
	}
	while (i < scmd->ntokens && scmd->tokens[i])
	{
		tmp = find_env(g_fcmd->envp, scmd->tokens[i]);
		if (tmp)
			g_fcmd->envp = remove_env(tmp);
		i++;
	}
}
