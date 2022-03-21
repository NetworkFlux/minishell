/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:10:45 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/21 14:45:52 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **buildins_cd(t_scmd *scmd, char **args)
{
	(void)args;
	int	res;

	if (scmd->ntokens != 2)
	{
		printf("bash: cd: too many arguments\n");
		return (args);
	}
	res = chdir(scmd->tokens[1]);
	if (res == -1)
		printf("bash: cd: %s: No such file or directory\n", scmd->tokens[1]);
	return (args);
}
