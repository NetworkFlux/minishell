/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:28:02 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/22 15:26:18 by npinheir         ###   ########.fr       */
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

/* checks if the single command exec is a builtin function */
/*
void	is_builtin(t_scmd *s_cmd, char **args, char *target)
{
	size_t		i;
	const char	*builtins[7] = {"exit", "cd",
		"env", "pwd", "unset", "echo", "export"};

	i = 0;
	while (i < 7 && builtins[i])
	{
		if (ft_strcompare(builtins[i], s_cmd->tokens[0]))
		{
			route_builtins(s_cmd, i, args);
			return ;
		}
		i++;
	}
	//printf("Child Process : %s is being executed\n", s_cmd->tokens[0]);
	// execvp(s_cmd->tokens[0], args);
	if (target == NULL)
	{
		printf("%s: command not found\n", s_cmd->tokens[0]);
		exit(127);
	}
	execve(target, args, g_fcmd->env);
	// if execve gets an error, it doesn't take possession of the child process
	// so it does not exit it
	exit(EXIT_FAILURE);
}
*/
