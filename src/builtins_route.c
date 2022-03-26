/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:28:02 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/26 14:35:58 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if the exec is a builtin and files permissions are ok,
// calls the appropriate function
// if no child process is executed sets exitcode to 0;
int	route_builtins(t_scmd *scmd, size_t i, int readpipe)
{
	int	new_piperead;

	new_piperead = 0;
	if (i == 0)
		builtins_exit(scmd);
	else if (i == 1)
		buildins_cd(scmd);
	else if (i == 2)
		new_piperead = builtins_env(scmd, readpipe);
	else if (i == 3)
		new_piperead = buildins_pwd(scmd, readpipe);
	else if (i == 4)
		builtin_unset(scmd);
	else if (i == 5)
		new_piperead = buildins_echo(scmd, readpipe);
	else if (i == 6)
		new_piperead = builtins_export(scmd, readpipe);
	g_fcmd->exitcode = 0;
	return (new_piperead);
}

//	checks if exec is a builtin
// returns -1 if not a builtin / index if it is
int	find_builtin(t_scmd *s_cmd)
{
	size_t		i;
	const char	*builtins[7] = {"exit", "cd",
		"env", "pwd", "unset", "echo", "export"};

	i = 0;
	if (!s_cmd->tokens || !s_cmd->tokens[0])
		return (-1);
	while (i < 7 && builtins[i])
	{
		if (ft_strcompare(builtins[i], s_cmd->tokens[0]))
			return (i);
		i++;
	}
	return (-1);
}
