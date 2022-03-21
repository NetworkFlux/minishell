/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:28:02 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/21 16:30:36 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if the exec is a builtin and files permissions are ok,
// calls the appropriate function
char **route_builtins(t_scmd *scmd, size_t i, char **args)
{
	if (i == 0)
		args = builtins_exit(scmd, args); // ok
	else if (i == 1)
		args = buildins_cd(scmd, args); // ok
	else if (i == 2)
		args = builtins_env(scmd, args); // output
	else if (i == 3)
		args = buildins_pwd(scmd, args); // output
	else if (i == 4)
		args = builtin_unset(scmd, args); // ok
	else if (i == 5)
		args = buildins_echo(scmd, args); // input && output
	else if (i == 6)
		args = builtins_export(scmd, args); // input && output
	// if no child process was executed
	g_fcmd->exitcode = 0;
	return (args);
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
