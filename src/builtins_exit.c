/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.42.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 11:16:55 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/24 11:22:21 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_exit(t_scmd *scmd)
{
	int		n;
	size_t	i;

	i = 0;
	if (scmd->ntokens > 2)
		perr(E2BIG, "bash: exit");
	else
	{
		ft_putendl_fd("exit", 1);
		if (scmd->tokens[1])
		{
			while (scmd->tokens[1][i])
			{
				if (!ft_isdigit(scmd->tokens[1][i]))
					clear_exit(1);
				i++;
			}
			n = ft_atoi(scmd->tokens[1]);
			clear_exit(n);
		}
		else
		{
			clear_exit(g_fcmd->exitcode);
		}
	}	
}
