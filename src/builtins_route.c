/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:28:02 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/22 16:23:40 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if the exec is a builtin and files permissions are ok,
// calls the appropriate function
int		route_builtins(t_scmd *scmd, size_t i, int readpipe)
{
	int	new_piperead;

	new_piperead = 0;
	if (i == 0)
		builtins_exit(scmd); // ok
	else if (i == 1)
		buildins_cd(scmd); // ok
	else if (i == 2)
		new_piperead = builtins_env(scmd, readpipe); // output
	else if (i == 3)
		new_piperead = buildins_pwd(scmd, readpipe); // output
	else if (i == 4)
		builtin_unset(scmd); // ok
	else if (i == 5)
		new_piperead = buildins_echo(scmd, readpipe); // input && output
	else if (i == 6)
		new_piperead = builtins_export(scmd, readpipe); // input && output
	// if no child process was executed
	g_fcmd->exitcode = 0;
	return (new_piperead);
}

//	checks if exec is a builtin
// returns -1 if not a builtin / index if it is
int		find_builtin(t_scmd *s_cmd)
{
	size_t		i;
	const char	*builtins[7] = {"exit", "cd",
		"env", "pwd", "unset", "echo", "export"};

	i = 0;
	while (i < 7 && builtins[i])
	{
		if (ft_strcompare(builtins[i], s_cmd->tokens[0]))
			return (i);
		i++;
	}
	return (-1);	
}
