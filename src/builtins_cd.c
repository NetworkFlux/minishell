/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:10:45 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/19 19:13:56 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	buildins_cd(t_scmd *scmd)
{
	int	res;

	if (scmd->ntokens != 2)
	{
		printf("<cd> No more than 1 parameter allowed\n");
		return ;
	}
	res = chdir(scmd->tokens[1]);
	if (res == -1)
		printf("Directory doesn't exist.\n");
}
